-- List all the movies released in 2010 and their ratings, in descending order by rating
SELECT title, rating FROM movies
INNER JOIN ratings ON movies.id = ratings.movie_id
WHERE year = '2010' ORDER BY ratings.rating DESC, movies.title;
