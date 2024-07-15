-- List the titles of the five highest rated movies (in order),
-- that Chadwick Boseman starred in, starting wth the highest rated.

-- Find the id of Chadwick Boseman
-- SELECT id from people
-- WHERE name = 'Chadwick Boseman';

-- Find the id's of movies associated with Chadwick Boseman's id
-- SELECT movie_id FROM stars
-- WHERE person_id = '1569276';

-- Find the movie titles with those id's
-- SELECT title FROM movies
-- JOIN ratings ON movies.id = ratings.movie_id
-- WHERE id = '8688634' ORDER BY ratings.rating LIMIT 5;

SELECT title FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE id IN (
    SELECT movie_id FROM stars
    WHERE person_id IN (
        SELECT id FROM people
        WHERE name = 'Chadwick Boseman'
    )
) ORDER BY ratings.rating DESC LIMIT 5;

