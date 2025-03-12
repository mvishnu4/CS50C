-- Keep a log of any SQL queries you execute as you solve the mystery.
--excuting schema to know tables in data base
--findind crime report that took place on 7-28 in Humpry Street as told in walkthrough
select description FROM crime_scene_reports WHERE day = 28 AND month = 7 AND street = 'Humphrey Street';
--Littering took place at 16:36. No known witnesses.
-- Trying to know transcript of interviews to know more information
SELECT transcript FROM interviews WHERE day = 28 AND month = 7 AND transcript LIKE '%bakery%';

--from the information of interviews i will take query of security logs,atmtransactions and flghts
SELECT * FROM bakery_security_logs WHERE day = 28 AND month = 7 AND hour = 10 AND activity = 'exit';
SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND hour = 10 AND activity = 'exit');

SELECT id, account_number, amount FROM atm_transactions WHERE atm_location = 'Leggett Street' AND day = 28 AND month = 7 AND transaction_type = 'withdraw';
--querying for licence platet and phone_number of theif
SELECT * FROM phone_calls WHERE month = 7 and day = 28 AND duration < 60;
SELECT * FROM people JOIN bank_accounts ON bank_accounts.person_id = people.id WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND hour = 10 AND activity = 'exit')
AND phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 and day = 28 AND duration < 60)
AND id IN (SELECT person_id FROM bank_accounts WHERE person_id IN (SELECT id FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND hour = 10 AND activity = 'exit')
AND phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 and day = 28 AND duration < 60)));

SELECT *  FROM airports WHERE city = 'Fiftyville';
--querying flight id of flight (that theif talked abuot in phone call: earliest flight) and ordering them by time
SELECT * FROM flights WHERE origin_airport_id = 8 AND month = 7 AND day = 28 OR day = 29 ORDER BY hour LIMIT 1;

SELECT * from passengers WHERE flight_id = 36 AND passport_number IN (
--Knowing the passenengers arrive in various destinations from the flights that taken off from Fiftyville
SELECT passport_number FROM passengers WHERE passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND hour = 10 AND activity = 'exit')
AND phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 and day = 28 AND duration < 60)
AND id IN (SELECT person_id FROM bank_accounts WHERE person_id IN
(SELECT id FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND hour = 10 AND activity = 'exit')))));


--comparing car owner licence plate and flight ticket destination taken by owner(theif)
SELECT * FROM people
WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND hour = 10 AND activity = 'exit')
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 4);

--Knowing the destination name of flight
SELECT * FROM airports WHERE id = 4;

--querying for call of suspect('Taylor')
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE month = 7 and day = 28 AND duration < 60 AND caller = (SELECT phone_number FROM people WHERE name = 'Bruce'));



--SELECT * from flights where destination_airport_id = 8 AND day = 28 and month = 7 ORDER BY hour;
