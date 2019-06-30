from flask import Flask, render_template, flash, redirect, url_for, session, logging
from data import Articles
from flask_mysqldb import mysql
from wtforms import Form, StringField, TextAreaField, PasswordField, validators
from passlib.hash import sha256_crypt

app = Flask(__name__)
app.debug = True
Articles = Articles()


@app.route('/')
def index():
    return render_template('index.html')
    
@app.route('/articles')
def articles():
    return render_template('articles.html', articles=Articles)
    
@app.route('/article/<string:id>/')
def article(id):
    return render_template('article.html', id=id)

if __name__ == '__main__':
    app.run()