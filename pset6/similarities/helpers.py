from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    return set([word for word in a.split('\n') if word in b.split('\n')])


def sentences(a, b):
    """Return sentences in both a and b"""
    return set([sent for sent in sent_tokenize(a) if sent in sent_tokenize(b)])


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    return set([sub for sub in substring(a, n) if sub in substring(b, n)])


def substring(a, n):
    size = len(a)
    list = []
    for i in range(size):
        if len(a[i:n + i]) == n:
            list.append(a[i:n + i])
    return list