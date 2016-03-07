<?php
/**
 * @author  Johan / Asbra <johan@asbra.net>
 *
 * @version 1.0
 * @date    2014-07-20
 */
$imdb_url = "http://www.imdb.com/user/{$imdb_id}/";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Get data
$data = file_get_contents($imdb_url);

$start = strpos($data, '<div class="widget article ratings">');
$end = strpos($data, '<div class="see-more">');

$data = substr($data, $start, $end - $start);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Get recent ratings
if (preg_match_all('/<div class="item">.*?<a href="(.+?)"><img src="(.+?)" width="([0-9]+)" height="([0-9]+)">.*?<a href="\/title\/(tt[0-9]+)\/">(.+?)<\/a>.*?<span class="their-rating only-rating" title="They rated this ([0-9]{1,2})\/10">([0-9]{1,2})<\/span><\/div>/smi', $data, $matches, PREG_SET_ORDER) === false) {
    die('Failed to find recent ratings');
}

$ratings = array();

foreach ($matches as $match) {
    // IMDB does not allow hotlinking
    // so we'll download the images we need, and store them locally
    $parts = explode('/', $match[2]);
    $image = end($parts);

    if (!file_exists("images/{$image}")) {
        file_put_contents("images/{$image}", file_get_contents($match[2]));
    }

    $rating = new StdClass();
    $rating->link = ltrim($match[1], '/');
    $rating->image = "images/{$image}";
    $rating->width = $match[3];
    $rating->height = $match[4];
    $rating->id = $match[5];
    $rating->title = $match[6];
    $rating->rating = (!empty($match[7]) ? $match[7] : $match[8]);
    $ratings[] = $rating;
}
