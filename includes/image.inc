<?php
/**
 * @author  Johan / Asbra <johan@asbra.net>
 *
 * @version 1.0
 * @date    2014-07-20
 */
if (empty($format)) {
    $format = 'png';
}

header("Content-Type: image/{$format}");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Cache
if (!isset($_GET['debug'])) {
    $cache_path = "cache/{$imdb_id}-{$width}x{$height}.{$format}";

    if (file_exists($cache_path)) {
        if ((time() - filemtime($cache_path)) <= 60 * 10) {
            // if data is more than 10 minutes old

      imagealphablending($image, false);
            imagesavealpha($image, true);
            imagepng($image);
            imagedestroy($image);
            exit;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Get data
require 'imdb.inc';

function text_outlined($image, $font, $x, $y, $text, $color, $outline)
{
    imagestring($image, $font, $x - 1, $y - 1, $text, $outline);
    imagestring($image, $font, $x, $y - 1, $text, $outline);
    imagestring($image, $font, $x + 1, $y - 1, $text, $outline);
    imagestring($image, $font, $x - 1, $y, $text, $outline);
    imagestring($image, $font, $x + 1, $y, $text, $outline);
    imagestring($image, $font, $x - 1, $y + 1, $text, $outline);
    imagestring($image, $font, $x, $y + 1, $text, $outline);
    imagestring($image, $font, $x + 1, $y + 1, $text, $outline);
    imagestring($image, $font, $x, $y, $text, $color);
}

$image = imagecreatetruecolor($width, $height);
imagealphablending($image, false);
$alpha_color = imagecolorallocatealpha($image, 255, 255, 255, 127);
imagefilledrectangle($image, 0, 0, $width, $height, $alpha_color);
imagealphablending($image, true);

$blue = imagecolorallocate($image, 67, 139, 197);
$grey = imagecolorallocate($image, 179, 179, 179);
$white = imagecolorallocate($image, 255, 255, 255);
$black = imagecolorallocate($image, 0, 0, 0);
$gray = imagecolorallocate($image, 85, 85, 85);

$nick_color = imagecolorallocate($image, 71, 135, 160);

// Add games
$x = 0;
$y = 0;

$used = array();

foreach ($games as $game) {
    $imghash = md5($game->image);

    if (file_exists("icons/{$imghash}.jpg")) {
        $game_icon = @imagecreatefromjpeg("icons/{$imghash}.jpg");
    } else {
        $game_icon = @imagecreatefromjpeg($game->image);
        file_put_contents("icons/{$imghash}.jpg", file_get_contents($game->image));
    }

    imagecopy($image, $game_icon, $x, $y, 0, 0, 32, 32);

    $used[] = $game->appid;

    $x += 32;

    if ($x >= $width) {
        if ($y >= $height) {
            break;
        }

        $x = 0;
        $y += 32;
    }
}

while ($y < $height || ($y >= $height && $x < $width)) {
    // We have empty space to fill! Grab some games from library..
  $r = mt_rand(0, count($owned->response->games) - 1);

    $game = $owned->response->games[$r];

    if (in_array($game->appid, $used)) {
        continue;
    }

    $game_image = "http://media.steampowered.com/steamcommunity/public/images/apps/{$game->appid}/{$game->img_icon_url}.jpg";
    $game_icon = @imagecreatefromjpeg($game_image);

    if ($game_icon == false) {
        continue;
    }

    imagecopy($image, $game_icon, $x, $y, 0, 0, 32, 32);

    $used[] = $game->appid;

    $x += 32;

    if ($x >= $width) {
        if ($y >= $height) {
            break;
        }

        $x = 0;
        $y += 32;
    }
}

// Add the avatar
$avatar_x = (($height - 74) / 2);
$avatar_y = (($height - 74) / 2);

imagefilledellipse($image, ($avatar_x + 6), ($avatar_y + 6), 12, 12, $black); // top left
imagefilledellipse($image, ($avatar_x + 67), ($avatar_y + 6), 12, 12, $black); // top right
imagefilledellipse($image, ($avatar_x + 6), ($avatar_y + 67), 12, 12, $black); // bottom left
imagefilledellipse($image, ($avatar_x + 67), ($avatar_y + 67), 12, 12, $black); // bottom right
imagefilledrectangle($image, ($avatar_x + 7), ($avatar_y + 0), ($avatar_y + 66), ($avatar_y + 73), $black);
imagefilledrectangle($image, ($avatar_x + 0), ($avatar_y + 7), ($avatar_y + 73), ($avatar_y + 67), $black);

imagefilledellipse($image, ($avatar_x + 7), ($avatar_y + 7), 12, 12, $nick_color); // top left
imagefilledellipse($image, ($avatar_x + 66), ($avatar_y + 7), 12, 12, $nick_color); // top right
imagefilledellipse($image, ($avatar_x + 7), ($avatar_y + 66), 12, 12, $nick_color); // bottom left
imagefilledellipse($image, ($avatar_x + 66), ($avatar_y + 66), 12, 12, $nick_color); // bottom right
imagefilledrectangle($image, ($avatar_x + 8), ($avatar_y + 1), ($avatar_x + 65), ($avatar_y + 72), $nick_color);
imagefilledrectangle($image, ($avatar_x + 1), ($avatar_y + 8), ($avatar_x + 72), ($avatar_y + 66), $nick_color);

$img_avatar = @imagecreatefromjpeg($profile->avatar_medium);
$img_avatar = roundedImage($img_avatar, 40, 64, 64);

imagecopy($image, $img_avatar, ($avatar_x + 5), ($avatar_y + 5), 0, 0, 64, 64); // 32x32 64x64 184x184

// Add Steam icon
$img_steam = @imagecreatefrompng('icons/steam.png');
imagecopy($image, $img_steam, $avatar_x, $avatar_y, 0, 0, 16, 16);

// Add Steam nickname
text_outlined($image, 1, ($avatar_x + 8), ($avatar_y + 59), $profile->nick, $white, $black);

imagealphablending($image, false);
imagesavealpha($image, true);

imagepng($image);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Save to cache
if (!isset($_GET['debug'])) {
    imagepng($image, "cache/{$steam_id}-{$width}x{$height}.{$format}");
}

imagedestroy($image);
