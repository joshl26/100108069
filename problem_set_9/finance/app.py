import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

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

    # create dictionary of all stocks owned (symbol, total_shares, current_price), summarized to one one line per stock."
    stocks = db.execute(
        "SELECT symbol, SUM(qty) AS qty, AVG(price) as price, SUM(total) AS [total] FROM transactions WHERE user_id = ? GROUP BY symbol",
        session["user_id"],
    )

    # Query database for current user
    rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

    # "find current cash for user signed in"
    cash = round(float(rows[0]["cash"]), 2)

    # total = cash + current value of stocks owned
    total = 0

    current_value = 0

    i = 0
    while i < len(stocks):
        quote = lookup(stocks[i]["symbol"])
        stocks[i]["price"] = quote["price"]
        stocks[i]["total"] = float(quote["price"]) * int(stocks[i]["qty"])
        current_value += stocks[i]["total"]
        i = i + 1

    total = round(cash + current_value, 2)

    return render_template("index.html", stocks=stocks, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        # Ensure symbol submitted is valid
        elif not lookup(request.form.get("symbol")):
            return apology("stock symbol not valid", 400)
        # Ensure number of shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide number of shares", 400)
        # Ensure number of shares is greater than zero
        elif int(request.form.get("shares")) == 0:
            return apology("must provide number of shares greater than zero", 400)

        quote = lookup(request.form.get("symbol"))

        price = float(quote["price"])

        shares = int(request.form.get("shares"))

        symbol = quote["symbol"]

        total = price * shares

        # Query database for current user
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        if total >= rows[0]["cash"]:
            return apology("value of shares purchased exceeds cash on hand!", 400)

        delta = rows[0]["cash"] - total

        # Insert new buy record into transactions table
        rows = db.execute(
            "INSERT INTO transactions (user_id, transaction_type, symbol, price, qty) VALUES (?, 'buy', ?, ?, ?)",
            session["user_id"],
            symbol,
            price,
            shares,
        )

        # Query database for current user
        rows = db.execute(
            "UPDATE users SET cash=? WHERE id=?", delta, session["user_id"]
        )

        if rows != 0:
            # Redirect user to home page
            return redirect("/")

        else:
            return apology("unable to purchase stock, try again", 400)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Insert new buy record into transactions table
    stocks = db.execute(
        "SELECT * FROM transactions WHERE user_id = ?", session["user_id"]
    )

    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 400)

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
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("symbol"):
            return apology("must provide a stock symbol", 400)

        if not lookup(request.form.get("symbol")):
            return apology("must provide a valid stock symbol", 400)

        quote = lookup(request.form.get("symbol"))

        # return render_template("quoted.html", lookup_text=request.form.get("symbol"), symbol=quote.symbol, price=quote.price)
        return render_template(
            "quoted.html",
            lookup_text=request.form.get("symbol"),
            symbol=quote["symbol"],
            price=round(quote["price"], 2),
        )

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password was re-submitted
        elif not request.form.get("confirmation"):
            return apology("must provide password, again", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 0:
            return apology("username already exists!", 400)

        if request.form.get("password") == request.form.get("confirmation"):
            hashedPassword = generate_password_hash(
                request.form.get("password"), method="scrypt", salt_length=16
            )
            # print(hashedPassword)

            # Query database for username
            rows = db.execute(
                "INSERT INTO users (username, hash) values (?, ?)",
                request.form.get("username"),
                hashedPassword,
            )

            if rows != 0:
                # Redirect user to home page
                return redirect("/")

            else:
                return apology("unable to insert new user", 400)

        else:
            return apology("password confirmation does not match!", 400)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reached route via POST (as by submitting a form via POST)

    if request.method == "POST":

        # # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        # Ensure symbol submitted is valid
        elif not lookup(request.form.get("symbol")):
            return apology("stock symbol not valid", 400)
        # Ensure number of shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide number of shares", 400)
        # Ensure number of shares is greater than zero

        try:
            shares_test = float(request.form.get("shares"))

            if request.form.get("shares") <= 0:
                return apology("must provide number of shares greater than zero", 400)

            elif shares_test != int(shares):
                return apology("must provide a whole number of shares", 400)

        except ValueError:
            return apology("must provide a numeric value", 400)

        # check to see if use owns any of stock symbol submitted, else return apology
        rows = db.execute(
            "SELECT * FROM transactions WHERE user_id = ? AND symbol = ?",
            session["user_id"],
            request.form.get("symbol"),
        )

        # check to see if a user owns shares of a certain symbol
        if len(rows) == 0:
            return apology("must provide a valid symbol that you own shares of", 400)

        # create dictionary of all stocks owned (symbol, total_shares, current_price), summarized to one one line per stock."
        symbol_total = db.execute(
            "SELECT symbol, SUM(qty) AS [total] FROM transactions WHERE user_id = ? AND symbol = ?",
            session["user_id"],
            request.form.get("symbol"),
        )

        print(symbol_total)

        # check to see if a user has enough shares to sell, if not print apology
        if int(request.form.get("shares")) > int(symbol_total[0]["total"]):
            return apology(
                "sorry you do not own that many shares, reduce the number submitted and try again.",
                400,
            )

        # find latest price using lookup
        latest_price = lookup(request.form.get("symbol"))

        # convert number of shares to negative
        shares = -int(request.form.get("shares"))

        # Query database for current user
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        # "find current cash for user signed in"
        cash = float(rows[0]["cash"])

        delta = cash + (int(request.form.get("shares")) * latest_price["price"])

        # Insert new sell record into transactions table
        rows = db.execute(
            "INSERT INTO transactions (user_id, transaction_type, symbol, price, qty) VALUES (?, 'sell', ?, ?, ?)",
            session["user_id"],
            request.form.get("symbol"),
            float(latest_price["price"]),
            shares,
        )

        # Query database for current user
        rows = db.execute(
            "UPDATE users SET cash=? WHERE id=?", delta, session["user_id"]
        )

        if rows != 0:
            # Redirect user to home page
            return redirect("/")

        else:
            return apology("unable to purchase stock, try again", 400)

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        # create dictionary of all stocks owned (symbol, total_shares, current_price), summarized to one one line per stock."
        stocks = db.execute(
            "SELECT symbol, SUM(qty) as qty, price, SUM(total) AS [total] FROM transactions WHERE user_id = ? GROUP BY symbol",
            session["user_id"],
        )

        return render_template("sell.html", stocks=stocks)
