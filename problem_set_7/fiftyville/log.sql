-- Harvard CS50X Problem Set Submission
-- Problem Set 7 - Fiftyville
-- By Joshua Lehman - May 27, 2024

-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Query the crime_scene_reports table for July 28, 2023, humphrey street
SELECT * FROM crime_scene_reports
WHERE year = '2023'
AND month = '7'
AND day = '28'
AND street LIKE '%Humphrey Street%';

-- The above query returns:
-- | 295 | 2023 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took
-- place at 10:15am at the Humphrey Street bakery. Interviews were conducted
-- today with three witnesses who were present at the time – each of their
-- interview transcripts mentions the bakery. |

-- Query interviews table for specific interviews (3 to be exact, per police report) on July 28, 2023
SELECT * FROM interviews
WHERE year = '2023'
AND month = '7'
AND day = '28';

-- Which returns the following relevant information:
-- | 163 | Raymond | 2023 | 7     | 28  | As the thief was leaving the bakery,
-- they called someone who talked to them for less than a minute. In the call,
-- I heard the thief say that they were planning to take the earliest flight
-- out of Fiftyville tomorrow. The thief then asked the person on the other end
-- of the phone to purchase the flight ticket. |

-- | 162 | Eugene  | 2023 | 7     | 28  | I don't know the thief's name, but it
-- was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing
-- some money.

-- | 161 | Ruth    | 2023 | 7     | 28  | Sometime within ten minutes of the theft,
-- I saw the thief get into a car in the bakery parking lot and drive away. If you have
-- security footage from the bakery parking lot, you might want to look for cars that
-- left the parking lot in that time frame.


-- the thief made a call for one minute while leaving the bakery asking someone to
-- buy plane tickets for a flight leaving fiftyville the next day

-- the thief lives in town and is a resident. Right before the robbery someone saw the thief
-- withdraw money from an ATM on Leggett St.

-- security footage from ten minutes after robbery should show some detail,
-- look for cars leaving at that time.

SELECT * FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE year = '2023'
AND month = '7'
AND day = '28'
AND atm_location LIKE '%Leggett Street%';

-- Returns the following:
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+----------------+-----------+---------------+--------+---------+----------------+-----------------+---------------+
-- | id  | account_number | year | month | day |  atm_location  | transaction_type | amount | account_number | person_id | creation_year |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+----------------+-----------+---------------+--------+---------+----------------+-----------------+---------------+
-- | 267 | 49610011       | 2023 | 7     | 28  | Leggett Street | withdraw         | 50     | 49610011       | 686048    | 2010          | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       | **
-- | 275 | 86363979       | 2023 | 7     | 28  | Leggett Street | deposit          | 10     | 86363979       | 948985    | 2010          | 948985 | Kaelyn  | (098) 555-1164 | 8304650265      | I449449       |
-- | 336 | 26013199       | 2023 | 7     | 28  | Leggett Street | withdraw         | 35     | 26013199       | 514354    | 2012          | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 269 | 16153065       | 2023 | 7     | 28  | Leggett Street | withdraw         | 80     | 16153065       | 458378    | 2012          | 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
-- | 264 | 28296815       | 2023 | 7     | 28  | Leggett Street | withdraw         | 20     | 28296815       | 395717    | 2014          | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
-- | 288 | 25506511       | 2023 | 7     | 28  | Leggett Street | withdraw         | 20     | 25506511       | 396669    | 2014          | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 246 | 28500762       | 2023 | 7     | 28  | Leggett Street | withdraw         | 48     | 28500762       | 467400    | 2014          | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       | **-
-- | 266 | 76054385       | 2023 | 7     | 28  | Leggett Street | withdraw         | 60     | 76054385       | 449774    | 2015          | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       | **
-- | 313 | 81061156       | 2023 | 7     | 28  | Leggett Street | withdraw         | 30     | 81061156       | 438727    | 2018          | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+----------------+-----------+---------------+--------+---------+----------------+-----------------+---------------+

-- Now we could search through all the flights booked for tomorrow for any of these
-- passport numbers, one of these is our robber! And by looking at the bookings
-- we may find our accomplice as well!

-- look into security footage from the bakery ten minutes after robbery
SELECT * FROM bakery_security_logs
WHERE year = '2023'
AND month ='7'
AND day = '28'
AND activity = 'exit'
AND hour = '10'
AND minute > 14
AND minute < 26;

-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | id  | year | month | day | hour | minute | activity | license_plate |
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | 260 | 2023 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
-- | 261 | 2023 | 7     | 28  | 10   | 18     | exit     | 94KL13X       | **
-- | 262 | 2023 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
-- | 263 | 2023 | 7     | 28  | 10   | 19     | exit     | 4328GD8       | **_
-- | 264 | 2023 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
-- | 265 | 2023 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
-- | 266 | 2023 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
-- | 267 | 2023 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
-- +-----+------+-------+-----+------+--------+----------+---------------+

-- look into phone logs from time of robbery, our prime suspect made a call
-- the accomplice!

SELECT * FROM phone_calls
WHERE year = '2023'
AND month = '7'
AND day = '28'
AND duration < '60'
ORDER BY duration;

--+-----+----------------+----------------+------+-------+-----+----------+
--| id  |     caller     |    receiver    | year | month | day | duration |
--+-----+----------------+----------------+------+-------+-----+----------+
--| 224 | (499) 555-9472 | (892) 555-8872 | 2023 | 7     | 28  | 36       |
--| 261 | (031) 555-6622 | (910) 555-3251 | 2023 | 7     | 28  | 38       |
--| 254 | (286) 555-6063 | (676) 555-6554 | 2023 | 7     | 28  | 43       |
--| 233 | (367) 555-5533 | (375) 555-8161 | 2023 | 7     | 28  | 45       |**
--| 255 | (770) 555-1861 | (725) 555-3243 | 2023 | 7     | 28  | 49       |
--| 251 | (499) 555-9472 | (717) 555-1342 | 2023 | 7     | 28  | 50       |
--| 221 | (130) 555-0289 | (996) 555-8899 | 2023 | 7     | 28  | 51       |
--| 281 | (338) 555-6650 | (704) 555-2131 | 2023 | 7     | 28  | 54       |
--| 279 | (826) 555-1652 | (066) 555-9701 | 2023 | 7     | 28  | 55       |
--+-----+----------------+----------------+------+-------+-----+----------+


SELECT * FROM people
WHERE phone_number = '(375) 555-8161';

-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 561160 | Kathryn | (609) 555-5876 | 6121106406      | 4ZY7I8T       |
-- +--------+---------+----------------+-----------------+---------------+

SELECT * FROM people
WHERE license_plate = '94KL13X';

--+--------+------+----------------+-----------------+---------------+
--|   id   | name |  phone_number  | passport_number | license_plate |
--+--------+------+----------------+-----------------+---------------+
--| 467400 | Luca | (389) 555-5198 | 8496433585      | 4328GD8       |
--+--------+------+----------------+-----------------+---------------+

SELECT * FROM passengers
WHERE passport_number = '8496433585';

--+-----------+-----------------+------+
--| flight_id | passport_number | seat |
--+-----------+-----------------+------+
--| 11        | 8496433585      | 5D   |
--| 36        | 8496433585      | 7B   |
--| 48        | 8496433585      | 7C   |
--+-----------+-----------------+------+

SELECT * FROM passengers
WHERE flight_id = '36';
--+-----------+-----------------+------+
--| flight_id | passport_number | seat |
--+-----------+-----------------+------+
--| 34        | 6121106406      | 2A   |
--+-----------+-----------------+------+

SELECT * FROM flights
WHERE id = '48';

--+----+-------------------+------------------------+------+-------+-----+------+--------+
--| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
--+----+-------------------+------------------------+------+-------+-----+------+--------+
--| 48 | 5                 | 8                      | 2023 | 7     | 30  | 18   | 28     |
--+----+-------------------+------------------------+------+-------+-----+------+--------+

SELECT * FROM airports;

--+----+--------------+-----------------------------------------+---------------+
--| id | abbreviation |                full_name                |     city      |
--+----+--------------+-----------------------------------------+---------------+
--| 1  | ORD          | O'Hare International Airport            | Chicago       |
--| 2  | PEK          | Beijing Capital International Airport   | Beijing       |
--| 3  | LAX          | Los Angeles International Airport       | Los Angeles   |
--| 4  | LGA          | LaGuardia Airport                       | New York City |
--| 5  | DFS          | Dallas/Fort Worth International Airport | Dallas        |
--| 6  | BOS          | Logan International Airport             | Boston        |
--| 7  | DXB          | Dubai International Airport             | Dubai         |
--| 8  | CSF          | Fiftyville Regional Airport             | Fiftyville    |
--| 9  | HND          | Tokyo International Airport             | Tokyo         |
--| 10 | CDG          | Charles de Gaulle Airport               | Paris         |
--| 11 | SFO          | San Francisco International Airport     | San Francisco |
--| 12 | DEL          | Indira Gandhi International Airport     | Delhi         |
--+----+--------------+-----------------------------------------+---------------+

SELECT * FROM flights
WHERE year = '2023'
AND month = '7'
AND day = '29'
AND origin_airport_id = '8' ORDER BY hour;

--+----+-------------------+------------------------+------+-------+-----+------+--------+
--| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
--+----+-------------------+------------------------+------+-------+-----+------+--------+
--| 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     | *** Luca going to New York!
--| 43 | 8                 | 1                      | 2023 | 7     | 29  | 9    | 30     |
--| 23 | 8                 | 11                     | 2023 | 7     | 29  | 12   | 15     |
--| 53 | 8                 | 9                      | 2023 | 7     | 29  | 15   | 20     |
--| 18 | 8                 | 6                      | 2023 | 7     | 29  | 16   | 0      |
--+----+-------------------+------------------------+------+-------+-----+------+--------+
