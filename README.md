# IMDb "recently rated" widget
Scrape IMDb to create a widget displaying the latest IMDb items you've rated, what score, link to it, and cover art

Project contains 2 templates, one HTML and one image; [HTML widget](https://dev.asbra.net/imdb/?u=ur33819608) [Image widget](https://dev.asbra.net/imdb/?u=ur33819608&t=2)

[Article for this project](https://asbra.net/php-imdb-my-ratings-widget/) (link to my blog)

## Installation
* Upload to server
* Give write permissions on `cache/` folder, .html cache will be saved there
* Give write permissions on `images/` folder, IMDb thumbnails will be saved there

### GET Variables
* `debug` if set, skips cache
* `t` type of widget/output (1 = HTML, 2 = Image)
* `w` width (default 248px for HTML, 640px for image)
* `h` height (default 280px for HTML, 96px for image)
* `f` image file format (only PNG for now)
* `c` count of movies to show (in HTML output)
* `u` IMDb profile ID or URL

### Information
Set GET variable `debug` if you want to skip cache.

* [includes/imdb.inc](includes/imdb.inc) contains the IMDb scraping
* [index.php](index.php) entry point, calls `imdb.inc` to get data, handles templating and cache

#### Templates
* [templates](templates/) folder contains templates, here you change the appearance of the widget
* Edit `main.inc`, minify it to `main.min.inc` and it will be used. If `main.min.inc` doesn't exist, `main.inc` is used.
