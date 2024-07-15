-- List the names of all people who starred in Toy Story

-- Select names
SELECT name
FROM people
WHERE id IN
(
    -- Select person id's
    SELECT person_id
    FROM stars
    WHERE movie_id = (

        -- Select Toy Story's ID
        SELECT id
        FROM movies
        WHERE title = 'Toy Story'

    )
);
