import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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

    # initialise cash funds amount
    cash_total = db.execute("SELECT cash FROM users WHERE id == :id", id = session["user_id"])[0]["cash"]
    cash = usd(cash_total)

    id = session["user_id"]
    stocks = db.execute("SELECT * FROM portfolio WHERE id == :id", id=id)

    # initialise grand total
    grand_total = cash_total

    for i in range(len(stocks)):

        # declare var with all stock info
        stock = lookup(stocks[i]["stock"])

        # declare qty. price and stock total
        qty = stocks[i]["qty"]
        price = stock["price"]
        total = qty * price

        # add fields to the 'stocks' defenition
        stocks[i]["company"] = stock["name"]
        stocks[i]["symbol"] = stock["symbol"]
        stocks[i]["shares"] = qty
        stocks[i]["price"] = usd(price)
        stocks[i]["total"] = usd(total)

        # add to grand_total every time a line is run
        grand_total += total

    # display total value of stocks and cash together
    return render_template("index.html", cash=cash, stocks=stocks, grand_total=usd(grand_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # declare symbol & qty
        symbol = request.form.get("symbol").upper()
        qty = request.form.get("shares")

        # Check symbol is entered
        if not symbol:
            return apology("must provide stock symbol", 400)

        # check qty of shares is entered
        if not qty:
            return apology("must provide stock qty", 400)

        # check for negative or fractional shares
        try:
            int(qty)
        except ValueError:
            return apology("Enter valid amount of shares", 400)

        qty = int(qty)
        if qty < 1:
            return apology("Enter valid amount of shares", 400)

        # retreive stock from API
        stock = lookup(symbol)

        # check symbol is real
        if not stock:
            return apology("symbol does not exist", 400)

        # declare user, price, total cost & available cash
        id = session["user_id"]
        price = stock["price"]
        value = float(price) * float(qty)
        cash = float(db.execute("SELECT cash FROM users WHERE id == :id", id=id)[0]["cash"])

        # check user has enough funds
        if value > cash:
            return apology("not enough funds", 400)

        # update user cash amount
        cash -= value
        db.execute("UPDATE users SET cash = :cash WHERE id == :id", id=id, cash=cash)

        # add transaction to history
        db.execute("INSERT INTO history (id, action, stock, price, date, qty) VALUES (:id, 'BUY', :symbol, :price, CURRENT_TIMESTAMP, :qty)", id=id, symbol=symbol, price=usd(price), qty=qty)

        # check if stock already exists in portfolio, add stock
        existing_stock = db.execute("SELECT * FROM portfolio WHERE id = :id AND stock = :stock", id=id, stock=symbol)
        if len(existing_stock) != 0:
            db.execute("UPDATE portfolio SET qty = qty + :qty WHERE stock == :stock", stock=symbol, qty=qty)
        else:
            db.execute("INSERT INTO portfolio (id, stock, qty) VALUES (:id, :stock, :qty)", id=id, stock=symbol, qty=qty)

        # return to home page
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Declare id
    id = session["user_id"]

    # Display history db into html
    history = db.execute("SELECT * FROM history WHERE id == :id ORDER BY date DESC", id=id)
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
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # initialise symbol
        stock=request.form.get("symbol")

        # Ensure symbol was submitted
        if not stock:
            return apology("must provide stock symbol", 400)

        # retreive stock data from api
        data=lookup(stock)

        # check symbol is real
        if not data:
            return apology("symbol does not exist", 400)

        # send stock data to html
        return render_template("quote_return.html", symbol=data["symbol"], name=data["name"], price=usd(data["price"]))

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # initialise cons
    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")


    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Query database if username already exists
        existing_user = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(existing_user) != 0:
            return apology("username already exists", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        #Check passwords match
        elif password != confirmation:
            return apology("passwords must match", 400)

        # Hash password
        hashedPW =  generate_password_hash(password, method = 'pbkdf2:sha256', salt_length = 8)

        # Add user to database
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hashedPW)


        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # declare id & stocks
    id = session["user_id"]
    stocks = db.execute("SELECT * FROM portfolio WHERE id == :id", id=id)

    # build list of possible stocks to be sold
    for i in range(len(stocks)):
        stocks[i]["index"] = int(i)

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # check selected stock exists
        if not request.form.get("symbol"):
            return apology("please select stock to sell", 400)

        # declare stock qty and qty of shares to be sold
        sold_qty = request.form.get("shares")
        symbol = request.form.get("symbol")

        # check qty of shares is entered
        if not sold_qty:
            return apology("must provide stock qty", 400)

        # check for negative or fractional shares
        try:
            int(sold_qty)
        except ValueError:
            return apology("Enter valid amount of shares", 400)

        sold_qty = int(sold_qty)
        if sold_qty < 1:
            return apology("Enter valid amount of shares", 400)

        # Check qty entry is a number
        if not str(sold_qty).isnumeric():
            return apology("Enter valid amount of shares", 400)

        # check user has the stock to be sold otherwise return an error
        if int(stocks[0]["qty"]) < int(sold_qty):
            return apology("Not enough shares to sell", 400)

        # declare current stock price & proceeds amount
        current_price = lookup(symbol)["price"]
        proceeds = float(current_price) * int(sold_qty)

        # remove amount of stock from portfolio
        db.execute("UPDATE portfolio SET qty = qty - :sold_qty WHERE stock == :stock", sold_qty=sold_qty, stock=symbol)

        # add proceeds of sale to user cash
        db.execute("UPDATE users SET cash = cash + :proceeds WHERE id = :id", proceeds=proceeds, id=id)

        # check portfolio for any stocks with 0 qty and remove
        db.execute("DELETE FROM portfolio WHERE qty == 0")


        return redirect("/")

    else:

        return render_template("sell.html", stocks=stocks)
