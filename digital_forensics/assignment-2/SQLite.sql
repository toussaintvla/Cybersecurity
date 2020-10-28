-- SQLite
-- SELECT target_path, total_bytes, (end_time - start_time) AS elapsed_time
-- FROM `downloads`
-- ORDER BY elapsed_time DESC
-- LIMIT 0,1;

-- SELECT DISTINCT * FROM `keyword_search_terms` GROUP BY term;

-- SELECT title, last_visit_time FROM `urls` WHERE title LIKE 'eastbourne%';

-- SELECT DISTINCT urls.title, urls.last_visit_time, visits.visit_time
-- FROM `urls`
-- INNER JOIN `visits` ON  urls.last_visit_time = visits.visit_time
-- -- WHERE title LIKE 'eastbourne%'
-- ORDER BY urls.last_visit_time DESC;

-- SELECT DISTINCT keyword_search_terms.term, urls.title, urls.last_visit_time
-- FROM `keyword_search_terms`
-- INNER JOIN `urls` ON  keyword_search_terms.url_id = urls.id
-- ORDER BY urls.last_visit_time DESC;

-- SELECT DISTINCT datetime(urls.last_visit_time / 1000000 - 11644473600, 'unixepoch') AS date_time, 
-- keyword_search_terms.term, urls.title, urls.last_visit_time 
-- FROM `keyword_search_terms` 
-- INNER JOIN `urls` 
-- ON  keyword_search_terms.url_id = urls.id
-- INNER JOIN `visits`
-- ON urls.id = visits.url
-- ORDER BY date_time DESC
-- LIMIT 0,1;

-- SELECT DISTINCT datetime(urls.last_visit_time / 1000000 - 11644473600, 'unixepoch') AS date_time, urls.title
-- FROM `visits`
-- INNER JOIN `urls` 
-- ON urls.id = visits.url
-- ORDER BY date_time DESC;