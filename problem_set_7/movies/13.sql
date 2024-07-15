-- List the names of all people who starred in a movie in which kevin bacon also  starred

-- Find the id of Kevin Bacon (the one born in 1958!)
-- SELECT id FROM people
-- WHERE name = 'Kevin Bacon'
-- AND birth = '1958';

-- Find the id's of movies associated with kevin bacons id
-- SELECT movie_id FROM stars
-- WHERE person_id = '102';

-- Find the id's of people associated with those movie id's, except kevin bacon!
-- SELECT person_id from stars
-- WHERE movie_id = '9833362'
-- AND person_id != '102';

-- Find the names of people with those people id's
-- SELECT name FROM people
-- WHERE id = '10500614';

SELECT name FROM people
WHERE id IN (
    SELECT person_id FROM stars
    WHERE person_id != '102'
    AND person_id != '9323132'
    AND movie_id IN (
        SELECT movie_id FROM stars
        WHERE person_id IN (
            SELECT id FROM people
            WHERE name = "Kevin Bacon"
            AND birth = '1958'
        )
    )
) ORDER BY name ASC;
