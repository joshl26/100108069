-- Determine the average rating of the all movies released in 2012

SELECT AVG(rating)
FROM ratings r
JOIN movies m ON r.movie_id = m.id
WHERE m.year = '2012';

