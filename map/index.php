<?php include "conn.php"; ?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Multi Marker Map </title>

    <script src="http://maps.google.com/maps/api/js?sensor=false"></script>
    
    <script>
        
    var marker;
      function initialize() {
        var infoWindow = new google.maps.InfoWindow;
        
        var mapOptions = {
          mapTypeId: google.maps.MapTypeId.ROADMAP
        } 
 
        var map = new google.maps.Map(document.getElementById('map-canvas'), mapOptions);
        var bounds = new google.maps.LatLngBounds();

        // Retrieve data from database
        <?php
            $query = mysqli_query($con,"select * from test");
            while ($data = mysqli_fetch_array($query))
            {
                $lat = $data['lat'];
                $long = $data['lon'];
                
                echo ("addMarker($lat, $lon);\n");                        
            }
          ?>
          
        // Proses of making marker 
        function addMarker(lat, lng, info) {
            var loc = new google.maps.LatLng(lat, lng);
            bounds.extend(loc);
            var marker = new google.maps.Marker({
                map: map,
                position: loc
            });       
            map.fitBounds(bounds);
            bindInfoWindow(marker, map, infoWindow, info);
         }
        
        // Displays information on markers that are clicked
        function bindInfoWindow(marker, map, infoWindow, html) {
          google.maps.event.addListener(marker, 'click', function() {
            infoWindow.setContent(html);
            infoWindow.open(map, marker);
          });
        }
 
        }
      google.maps.event.addDomListener(window, 'load', initialize);
    
    </script>
    
</head>
<body onload="initialize()">
<nav class="navbar navbar-default navbar-fixed-top">
    <div class="container">
        <div class="navbar-header">
            <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
                <span class="icon-bar"></span><span class="icon-bar"></span><span class="icon-bar"></span>
            </button>
            <a class="navbar-brand" href="index.html">
            Pusat Ilmu Secara Detil</a>
        </div>
        <div class="navbar-collapse collapse">
            <ul class="nav navbar-nav navbar-left">
                <li class="clr1 active"><a href="index.html">Home</a></li>
                <li class="clr2"><a href="">Programming</a></li>
                <li class="clr3"><a href="">English</a></li>
            </ul>
        </div>
    </div>
</nav>
</br></br></br></br>  
<div class="container" style="margin-top:10px"> 

    <div class="row">
        <div class="col-md-8">
            <div class="panel panel-default">
                <div class="panel-heading">Marker Google Maps</div>
                    <div class="panel-body">
                        <div id="map-canvas" style="width: 700px; height: 600px;"></div>
                    </div>
            </div>
        </div>  
    </div>
</div>  
</body>
</html>