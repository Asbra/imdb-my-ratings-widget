<html>
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <style>
      body, html {
        margin:     0;
        padding:    0;
        background: none transparent;
      }

      a, a:visited, a:hover, a:link { color: #555; text-decoration: none; }

      p { margin: 10px 0; }
      .clear { clear: both; }

      .wrapper {
        width:       300px;
        color:       #555;
        font-family: 'Open Sans', Helvetica, Arial, sans-serif;
        font-size:   12px;
        line-height: 10px;
      }

      .row { width: 100%; }
      .col { display: inline-block; overflow: hidden; vertical-align: top; }
      .col-1 { width: 16px; }
      .col-2 { width: 32px; }
      .col-3 { width: 48px; }
      .col-4 { width: 64px; }
      .col-5 { width: 80px; }
      .col-6 { width: 96px; }
      .col-7 { width: 112px; }
      .col-8 { width: 128px; }
      .col-9 { width: 144px; }
      .col-10 { width: 160px; }
      .col-11 { width: 176px; }
      .col-12 { width: 192px; }
      .col-13 { width: 208px; }
      .col-14 { width: 224px; }
      .col-15 { width: 240px; }
      .col-16 { width: 256px; }

      .rating-star {
        background: url(images/sprites.png) repeat-x;
        background-position: 0 -27px;
        height:     13px;
        width:      13px;
        display:    inline-block;
      }
      .rating-star.rating-your { background-position: 0 -41px; }
    </style>
  </head>
  <body>
    <div class="wrapper">
      <?php foreach ($ratings as $rating) : ?>
        <div class="row">
            <div class="col col-3">
              <a href="http://www.imdb.com/<?= $rating->link ?>" target="_blank">
                <img src="<?= $rating->image ?>" title="<?= $rating->title ?>" width="41" height="60" />
              </a>
            </div>
            <div class="col col-13">
              <p>
                <a href="http://www.imdb.com/<?= $rating->link ?>" target="_blank">
                  <?= $rating->title ?>
                </a>
              </p>
              <div class="rating">
                <span class="rating-stars">
                  <?php for ($i = 1; $i <= 10; ++$i) : ?><span class="rating-star <?= ($rating->rating >= $i ? 'rating-your' : '') ?>"></span><?php endfor; ?>
                </span>
                <span class="rating-rating">&nbsp;<?= $rating->rating ?>/10</span>
              </div>
            </div>
        </div>
      <?php endforeach; ?>
    </div>
  </body>
</html>
