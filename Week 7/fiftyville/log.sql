-- Keep a log of any SQL queries you execute as you solve the mystery.

-- check crime_scene_reports for the date time and location of crime
SELECT *
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

--Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- check interviews that mention the word bakery
SELECT *
FROM interviews
WHERE transcript LIKE '%bakery%';


------------------------------ FOR THIEF --------------------

SELECT name
FROM people
-- The crime happened at 10:15 and the theif was spotted leaving the bakery within 10 mins after the robbery, check the bakery security logs
WHERE license_plate IN
    (SELECT license_plate FROM bakery_security_logs
    WHERE month = 7 AND day = 28
    AND ((activity = 'entrance' AND hour <= 9) OR (hour = 10 AND minute <= 15))
    AND license_plate IN
        (SELECT license_plate FROM bakery_security_logs
        WHERE month = 7 AND day = 28
        AND ((activity = 'exit' AND hour = 10 AND minute >= 15 AND minute <= 30))))

-- The interviews mention the theif was spotted using an atm prior withdrawing money prior to the robbery. Check who used the ATM on Leggett Street just prior to the robbery
AND id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN
    (SELECT account_number FROM atm_transactions
        WHERE month = 7 AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'))

-- The interviews mention the theif called someone on the phone as they left. The call lasted less than 1 min, Check for calls placed on the day fro < 1 min
AND id IN
    (SELECT id FROM people WHERE phone_number IN
    (SELECT caller FROM phone_calls
        WHERE month = 7 AND day = 28
        AND duration < 60))

-- The thief mentioned they would catch the earliest flight out on the following day
AND id IN
    (SELECT id FROM people WHERE passport_number IN
    (SELECT passport_number FROM passengers WHERE flight_id IN
    (SELECT id FROM flights
        WHERE origin_airport_id = 8
        AND month = 7 AND day = 29 and hour = (SELECT MIN(hour) FROM flights WHERE origin_airport_id = 8 AND month = 7 AND day = 29))));

------------------------------ FOR ACCOMPLICE --------------------

-- search people who received calls from the thief on the day for < 1 min
SELECT name
FROM people
WHERE id IN
    (SELECT id FROM people WHERE phone_number IN
    (SELECT receiver FROM phone_calls
        WHERE month = 7 AND day = 28
        AND duration < 60
        AND caller IN
        (SELECT phone_number FROM people WHERE name = 'Bruce')));

------------------------------ FOR DESTINATION CITY --------------------

-- search which city the earliest flight out of the Fiftyville went to
SELECT city
FROM airports
WHERE id IN
    (SELECT destination_airport_id FROM flights
        WHERE origin_airport_id = 8
        AND month = 7 AND day = 29 and hour = (SELECT MIN(hour) FROM flights WHERE origin_airport_id = 8 AND month = 7 AND day = 29));














