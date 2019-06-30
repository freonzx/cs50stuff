from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    portifolio = db.execute("SELECT * FROM portifolio WHERE owner=:id", id=session["user_id"])
    user_cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]['cash']

    updated_stock = []

    for stock in portifolio:
        quote = lookup(stock['symbol'])
        updated_stock.append({'symbol': stock['symbol'], 'name': stock['name'], 'price': quote['price'],
                              'quantity': stock['quantity'], 'total': (stock['quantity'] * quote['price'])})

    return render_template("index.html", cash=usd(user_cash), portifolio=updated_stock)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must provide a symbol", 400)

        elif not request.form.get("shares"):
            return apology("must provide a share number", 400)
        elif not request.form.get("shares").isdigit():
            return apology("must provide a share number", 400)
        elif not float(request.form.get("shares")) >= 1:
            return apology("must provide a share number", 400)

        quantity = request.form.get("shares")
        quote = lookup(request.form.get("symbol"))
        portifolio = db.execute("SELECT * FROM portifolio WHERE symbol=:symbol AND owner=:id",
                                symbol=request.form.get("symbol").upper(), id=session["user_id"])

        if not quote:
            return apology("quote not found", 400)

        user_cash = db.execute("SELECT cash FROM users WHERE id = :id",
                               id=session["user_id"])[0]['cash']
        total = float(quantity) * quote['price']
        if user_cash < total:
            return apology("You don't have enough cash", 400)
        elif portifolio:
            db.execute("UPDATE portifolio SET price = :price, quantity = :quantity, total = :total WHERE owner=:id AND symbol=:symbol",
                       price=quote['price'], quantity=int(quantity) + portifolio[0]['quantity'], total=total, id=session["user_id"], symbol=quote['symbol'])
        else:
            result = db.execute("INSERT INTO portifolio (owner, price, quantity, symbol, name, total) VALUES (:owner, :price, :quantity, :symbol, :name, :total)",
                                owner=session["user_id"], price=quote['price'], quantity=quantity, symbol=quote['symbol'], name=quote['name'], total=total)

            if not result:
                return apology("something went wrong", 400)

            new_balance = user_cash - total

            #
            result = db.execute("UPDATE users SET cash = :cash WHERE id=:id", cash=new_balance, id=session["user_id"])

            if not result:
                return apology("something went wrong", 400)

        db.execute("INSERT INTO trans (symbol, quantity, total, owner) VALUES (:symbol, :quantity, :total, :owner)",
                   symbol=quote['symbol'], quantity=quantity, total=total, owner=session["user_id"])

        flash('You successfully bought some stocks.')
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM trans WHERE owner=:id", id=session["user_id"])

    if not history:
        return apology("You don't have history", 400)
    else:
        return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash('Welcome.')
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide a symbol", 400)

        quote = lookup(request.form.get("symbol"))

        if not quote:
            return apology("quote not found", 400)

        return render_template("showQuote.html", data=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():

    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)
        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("passwords don't match", 400)

        # Query database for username
        pass_hash = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8)
        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :password)",
                            username=request.form.get("username"), password=pass_hash)

        if not result:
            return apology("username already taken", 400)

        session["user_id"] = result
        return redirect("/")
    else:
        return render_template("register.html")
    """Register user"""
    # return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        # Ensure password was submitted
        elif not request.form.get("shares"):
            return apology("must provide shares", 400)

        quote = lookup(request.form.get("symbol"))
        portifolio = db.execute("SELECT * FROM portifolio WHERE symbol=:symbol AND owner=:id",
                                symbol=request.form.get("symbol"), id=session["user_id"])

        if not portifolio:
            return apology("don't have a portifolio", 400)

        quantity = int(request.form.get("shares"))
        total = float(quantity) * quote['price']

        if portifolio[0]['quantity'] < int(request.form.get("shares")):
            return apology("don't have enough shares", 400)

        user_cash = db.execute("SELECT cash FROM users WHERE id = :id",
                               id=session["user_id"])[0]['cash']
        inflow = float(quote['price']) * float(request.form.get("shares"))
        new_balance = user_cash + inflow

        result = db.execute("UPDATE users SET cash = :cash WHERE id=:id", cash=new_balance, id=session["user_id"])
        if not result:
            return apology("something went wrong", 400)

        new_quantity = portifolio[0]['quantity'] - int(request.form.get("shares"))

        if new_quantity > 0:
            result = db.execute("UPDATE portifolio SET quantity = :quantity WHERE owner=:id and symbol = :symbol",
                                quantity=new_quantity, id=session["user_id"], symbol=request.form.get("symbol"))
        else:
            db.execute("DELETE FROM portifolio WHERE owner=:id AND symbol=:symbol",
                       id=session["user_id"], symbol=request.form.get("symbol"))

        if not result:
            return apology("something went wrong", 400)

        db.execute("INSERT INTO trans (symbol, quantity, total, owner) VALUES (:symbol, :quantity, :total, :owner)",
                   symbol=quote['symbol'], quantity=-quantity, total=total, owner=session["user_id"])

        flash('You successfully sold some stocks.')
        return redirect("/")

    portifolio = db.execute("SELECT * FROM portifolio WHERE owner=:id", id=session["user_id"])
    return render_template("sell.html", data=portifolio)


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    if request.method == "POST":
        if not request.form.get("cashammount"):
            return apology("must provide cash ammount", 400)
        elif not request.form.get("cashammount").isdigit():
            return apology("must provide a cash ammount", 400)
        elif not float(request.form.get("cashammount")) >= 1:
            return apology("must provide a cash ammount", 400)
        elif float(request.form.get("cashammount")) >= 10000:
            return apology("maximum deposit 10k", 400)

        cashammount = float(request.form.get("cashammount"))
        user_cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]['cash']

        if user_cash >= 1000000:
            return apology("cash limit reached", 400)

        new_b = user_cash + cashammount

        db.execute("UPDATE users SET cash = :cash WHERE id=:id", cash=new_b, id=session["user_id"])

        flash("Cash ammount added to your account.")
        return redirect("/")

    return render_template("addcash.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
