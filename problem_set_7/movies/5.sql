-- List the titles and releases of all Harry Potter movies, in chronological order

SELECT year, title
FROM movies
WHERE title LIKE 'Harry Potter%';
