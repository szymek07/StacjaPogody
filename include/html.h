const char HTTP_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pl" style="height:100;">
    <head>
     <meta charset="UTF-8">
     <style>
        body { font-size: 1.2rem; line-height: 1.6; font-weight: 300;font-family: "Raleway", "HelveticaNeue", "Helvetica Neue", Helvetica, Arial, sans-serif; color: rgb(13, 24, 12); background-color: white;}
        small {font-size: 0.7rem; }
        .big {font-size: 1.8rem; font-weight: 1000;}
        .med {font-size: 1.2rem; font-weight: 500;}
        .container {position: relative; margin: 0 auto;}
        .grid-container {position: relative;max-width: var(--grid-max-width);margin: 0 auto;padding: 10px;text-align: center;display: grid; grid-gap: 10px;gap: 10px;}
        .grid-container.quarters { grid-template-columns: repeat(4, 1fr); border-radius: 4px;}
        .grid-container.half { grid-template-columns: repeat(2, 1fr); border-radius: 4px;}
        section { border-radius: 4px; border: 2px solid rgb(13, 24, 12); margin-top: 5px; padding: 5px; max-width: 1024px; }
        .input {border-radius: 4px; border: 2px solid rgb(13, 24, 12); width: 200px; height: 30px; font-size: 1.2rem; font-family: "Raleway", "HelveticaNeue", "Helvetica Neue", Helvetica, Arial, sans-serif; color: rgb(13, 24, 12); background-color: white;}
        .input_long {border-radius: 4px; border: 2px solid rgb(13, 24, 12); width: 450px; height: 30px; font-size: 1.2rem; font-family: "Raleway", "HelveticaNeue", "Helvetica Neue", Helvetica, Arial, sans-serif; color: rgb(13, 24, 12); background-color: white;}
        .input_short {border-radius: 4px; border: 2px solid rgb(13, 24, 12); width: 37px; height: 30px; font-size: 1.2rem; font-family: "Raleway", "HelveticaNeue", "Helvetica Neue", Helvetica, Arial, sans-serif; color: rgb(13, 24, 12); background-color: white;}
        .box {border-radius: 4px; width: 32px; height: 32px; border: 2px solid; color: rgb(13, 24, 12);}
        .submit_btn {border-radius: 4px; border: 2px solid rgb(13, 24, 12); width: 980px; height: 30px; font-size: 1.2rem; font-family: "Raleway", "HelveticaNeue", "Helvetica Neue", Helvetica, Arial, sans-serif; color: white; background-color: rgb(4, 87, 4);}
    </style>
        <script type="text/javascript">

            window.onload = function (){
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        const response = JSON.parse(this.responseText);
                        for (const [key, value] of Object.entries(response)) {
                            let element = document.getElementById(key);
                            if (element){
                                if (element.type && element.type == "checkbox"){
                                    element.checked = value;
                                } else {
                                    element.value = value;
                                    element.innerHTML = value;
                                }
                            }
                        }                   
                    }
                };
                xhttp.open("GET", "/json.htm", true);
                xhttp.send();
            }

            function refresh_data(){
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        const response = JSON.parse(this.responseText);
                        for (const [key, value] of Object.entries(response)) {
                            let element = document.getElementById(key);
                            if (element){
                                if (element.type && element.type == "checkbox"){
                                } else {
                                    element.innerHTML = value;
                                }
                            }
                        }                   
                    }
                };
                xhttp.open("GET", "/json.htm?type=devices&rid=1", true);
                xhttp.send();
            }
            refresh_data();
            setInterval(refresh_data, 3000);        
        </script>
    </head>
    <body>
    <center>
    <div class="container">

        <section>
            <div class="grid-container full">
                <table cellspacing=0 cellpadding=0 border=0>
                    <tr>
                        <td width=70>
                            <a href="/">
                                <img src=" data:image/png;base64,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">
                            </a>
                        </td>
                        <td width=70>
                            <a href="/set_wifi">
                                <img src=" data:image/png;base64,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">
                            </a>
                        </td>                           
                        <td width=70>
                            <a href="/settings">
                                <img src=" data:image/png;base64,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">
                            </a>
                        </td>                                                                                                                        
                        <td>&nbsp;</td>
                        <td width=300><h2> <b id="gardner_name">wait...</b><b></b></h2></td>
                    </tr>
                </table>
            </div>
        </section> 
        <section>
            <div class="grid-container full"><big><b>Parametry</b></big></div>
            <div class="grid-container quarters">
                <div>
                    <label for="Temp">Temperatura</label><br>
                    <big class=big> <b id="Temp">wait...</b><b>C</b></big><br><br>
                </div>
                <div>
                    <label for="Humidity">Wilgotność</label><br>
                    <big class=big> <b id="Humidity">wait...</b><b>%Rh</b></big><br><br>
                </div>
                <div>
                    <label for="DewPoint">Punkt Rosy</label><br>
                    <big class=big> <b id="DewPoint">wait...</b><b>C</b></big><br><br>
                </div>
                <div>
                    <label for="Barometer">Ciśnienie</label><br>
                    <big class=big> <b id="Barometer">wait...</b><b>hPa</b></big><br><br>
                </div>                
            </div>
            <div class="grid-container quarters">
                <div>
                    <label for="Wind">Prędkość wiatru<br><small>(średnia z ostatniej minuty)</small></label><br>
                    <big class=big><b id="Wind">wait...</b><b>m/s</b></big><br><big class=med>(<b id="WindKMH">wait...</b><b> km/h</b>)</big>
                </div> 
                <div>
                    <label for="Gust">Poryw wiatru<br><small>(maximum z ostatnich 5 minut)</small></label>
                    <big class=big><b id="Gust">wait...</b><b>m/s</b></big><br><big class=med>(<b id="GustKMH">wait...</b><b> km/h</b>)</big>
                </div>  
                <div>
                    <label for="sensor_windchill">Temperatura odczuwalna</label><br><br>
                    <big class=big><b id="sensor_windchill">wait...</b><b>C</b></big>
                </div>                                              
            </div>
            <div class="grid-container full"><b id="job_status">Analizuję dane...</b></div>
        </section>
        <section>
            <div class="grid-container full">
                <small><b>SINUX @ 2021</b>
                    <br><b id="version">wait...</b>
                </small>
            </div>
        </section>  
    </div>
    </center>
    </body>
    </html>
)=====";