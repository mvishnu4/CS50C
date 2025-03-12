import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from math import ceil
from helpers import apology, login_required, lookup, usd


import sqlite3
conn = sqlite3.connect('finance.db')

user_id = 0
# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


#left<!--    <td class="data">{{stock["price"] | usd}}</td> -->
@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    if request.method == "POST":
        stock = request.form.get("symbol")
        if lookup(stock) != []:
            return render_template("quote.html", stocks=stock)
        else:
            return apology("something is missing", 400)
    else:
        stockcollection = []
        netflix = lookup("NFLX")
        stockcollection.append(netflix)
        tata= lookup("TCS.BO")
        stockcollection.append(tata)
        print(stockcollection)
        return render_template("quoted.html", stocks=stockcollection)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method =="POST":
        sym = request.form.get("symbol")
        share = request.form.get("shares")
        #print(sym)
        #print(share)
        #if (sym == ""):
           # return apology("No symbol provided")#render_template("/buy.html")
       # elif not(int(share)):
           # return apology("invalid stock price", 400)#render_template("/buy.html")#apology("Shares should be a positiive number")
        try:
            if not(lookup(sym)):
                return apology("Invalid stock")
        except:
                return apology("Invalid share price")
        try:
            share = int(request.form.get("shares"))
            if share < 0:
                return apology("Shares are invalid")
        except:
            return apology("Shares are invalid")

       # id = session["user_id"]
       # balance = db.execute( "SELECT cash FROM users WHERE id = id" )
       # if int(balance[0]["cash"]) > ceil(int(share)):
          #  conn.execute("CREATE IF NOT EXISTS purchases (cost NUMERIC NOT NULL, BALANCE NUMERIC NOT NULL)")
          #  db.execute("UPDATE users, SET cash = cash - share where id = id")
            #user = db.execute("SELECT * FROM users")
            #print(user)
            #return render_template("buy.html")
        #else:
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    return render_template("history.html")


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

        try:
            # Query database for username
            rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        except:
            return apology("No users are registered yet with the given name!")

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        print(rows)
        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
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
    return render_template("login.html")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method =="POST":
        qs = request.form.get("symbol")
        if not(lookup(qs)):
            return apology("Symbol not specified")
        else:
            return render_template("quoted.html", stocks=qs)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("Username is required", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Password confirmation is wrong try again", 400)

        elif db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username")):
            return apology("User with the name exists Choose another name!", 400)


        hashed = generate_password_hash(request.form.get("password"))

        rows = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), hashed)
        id = db.execute("SELECT * FROM users")
        #print(id)
        session["user_id"] = id[0]["id"]
        return redirect("/quote")
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        sym = request.form.get("symbol")
        print("symbol:")
        print(sym)
        if lookup(sym) != []:
            return render_template("quoted.html", stocks=sym)
        else:
            return apology("something is missing", 400)

        return render_template("quoted.html")
    else:
        return render_template("sell.html")
