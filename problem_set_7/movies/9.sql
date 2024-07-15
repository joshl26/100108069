-- List the names of all people who starred in a movie released in 2004, ordered by birth year

-- Find the id's of movies released in 2004
-- SELECT id FROM movies
-- WHERE year ='2004';

-- Find the id's of people who starred in these movies
-- SELECT person_id FROM stars
-- WHERE movie_id = '29593564';

-- Find the names of people with those people id's
-- SELECT name FROM people
-- WHERE id = '15364346';

-- Nest the previous queries, and order the result by birth year

SELECT name FROM people
where id IN (
    SELECT person_id FROM stars
    WHERE movie_id IN (
        SELECT id FROM movies
        WHERE year = '2004'
    )
) ORDER BY birth;
