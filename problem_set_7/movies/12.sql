-- List the titles of all the movies in which Bradley Cooper and Jennifer Lawrence starred

-- Find the id of Bradley Cooper
-- SELECT id FROM people
-- WHERE name = 'Bradley Cooper';

-- Find te id of Jennifer Lawrence
-- SELECT id FROM people
-- WHERE name = 'Jennifer Lawrence';

-- Find the id's of movies associated with Bradley Coopers id
-- SELECT movie_id FROM stars
-- WHERE person_id = '177896';

-- Find the id's of movies associated with Jennifer Lawrence's id
-- SELECT movie_id FROM stars
-- WHERE person_id = '2225369';

-- Find movie titles from the movie id's associated with both
-- Bradley Cooper and Jennifer Lawrence

-- SELECT title FROM movies
-- WHERE id IN (
--     SELECT movie_id FROM stars
--     WHERE person_id IN (
--         SELECT id FROM people
--         WHERE name IN ('Bradley Cooper', 'Jennifer Lawrence')
--     )
-- ) ORDER BY title;


SELECT m.title
FROM movies m
INNER JOIN stars s1 ON m.id = s1.movie_id
INNER JOIN stars s2 ON m.id = s2.movie_id
INNER JOIN people p1 ON s1.person_id = p1.id
INNER JOIN people p2 ON s2.person_id = p2.id
WHERE p1.name = 'Bradley Cooper'
AND p2.name = 'Jennifer Lawrence';
