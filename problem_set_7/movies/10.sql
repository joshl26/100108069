-- List the names of all people who have directed a movie that received a rating of at least 9.0

-- -- Find the id's of movies with at least a 9.0 rating
-- SELECT movie_id FROM ratings
-- WHERE rating >= 9.0;

-- Find the id's of people who directed those movies
-- SELECT person_id FROM directors
-- WHERE movie_id = '9900388';

-- Find the names of the people with those people id's
-- SELECT name FROM people
-- WHERE id = '10531593';

SELECT name FROM people
WHERE id IN (
    SELECT person_id FROM directors
    WHERE movie_id IN (
        SELECT movie_id FROM ratings
        WHERE rating >= 9.0
    )
) ORDER BY name;
