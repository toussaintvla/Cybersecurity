SELECT *
FROM wine w, winery wi
WHERE w.wine_id = wi.winery_id
AND w.description IS NOT NULL
GROUP BY w.wine_id;