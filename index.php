<?php
/**
 * @author  Johan / Asbra <johan@asbra.net>
 *
 * @version 1.0
 * @date    2014-07-20
 */
date_default_timezone_set('UTC');

if (!isset($_GET['u']) || empty($_GET['u'])) {
    echo <<<END
<br>
<center>
  Enter your IMDB profile URL (eg. <a href="http://www.imdb.com/user/ur33819608/">ur33819608</a>)
  <br />
  <form method="GET">
    <input type="text" size="40" name="u" /><input type="submit" value="Ok" />
  </form>
</center>
END;

    exit;
}

$imdb_id = strtolower($_GET['u']);

if (substr($imdb_id, 0, 4) == 'http') {
    preg_match('/user\/(ur[0-9]+)/i', $imdb_id, $matches);

    if (!isset($matches[1]) || empty($matches[1])) {
        die('Invalid ID!');
    }

    $imdb_id = $matches[1];
}

if (substr($imdb_id, 0, 2) != 'ur') {
    die('Invalid ID!');
}

$type = isset($_GET['t']) ? intval($_GET['t']) : 1; // 1 = HTML, 2 = Image
$format = isset($_GET['f']) ? strtolower($_GET['f']) : '';

$width = isset($_GET['w']) ? intval($_GET['w']) : ($type == 2 ? 640 : 248);
$height = isset($_GET['h']) ? intval($_GET['h']) : ($type == 2 ? 96 : 280);
$count = isset($_GET['c']) ? intval($_GET['c']) : 5;

$debug = isset($_GET['debug']);

if ($type == 2) {
    require 'includes/image.inc';
} else {
    require 'includes/html.inc';
}
