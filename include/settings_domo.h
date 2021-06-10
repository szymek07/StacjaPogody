const char HTTP_DOMO[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pl" style="height:100;">
    <head>
     <meta charset="UTF-8">
     <style>
        body { font-size: 1.2rem; line-height: 1.6; font-weight: 300;font-family: "Raleway", "HelveticaNeue", "Helvetica Neue", Helvetica, Arial, sans-serif; color: #ffffff; background-color: #4b4b4b;}
        small {font-size: 0.7rem; }
        .big {font-size: 1.8rem; font-weight: 1000;}
        .med {font-size: 1.2rem; font-weight: 500;}
        .container {position: relative; margin: 0 auto;}
        .grid-container {position: relative;max-width: var(--grid-max-width);margin: 0 auto;padding: 10px;text-align: center;display: grid; grid-gap: 10px;gap: 10px;}
        .grid-container.quarters { grid-template-columns: repeat(4, 1fr); border-radius: 4px;}
        .grid-container.half { grid-template-columns: repeat(2, 1fr); border-radius: 4px;}
        section { border-radius: 4px; border: 2px solid #ffffff; margin-top: 5px; padding: 5px; max-width: 1024px; }
        .input {border-radius: 4px; border: 2px solid #ffffff; width: 200px; height: 30px; font-size: 1.2rem; font-family: "Raleway", "HelveticaNeue", "Helvetica Neue", Helvetica, Arial, sans-serif; color: #ffffff; background-color: #3b3b3b;}
        .input_long {border-radius: 4px; border: 2px solid #ffffff; width: 450px; height: 30px; font-size: 1.2rem; font-family: "Raleway", "HelveticaNeue", "Helvetica Neue", Helvetica, Arial, sans-serif; color: #ffffff; background-color: #3b3b3b;}
        .input_short {border-radius: 4px; border: 2px solid #ffffff; width: 37px; height: 30px; font-size: 1.2rem; font-family: "Raleway", "HelveticaNeue", "Helvetica Neue", Helvetica, Arial, sans-serif; color: #ffffff; background-color: #3b3b3b;}
        .box {border-radius: 4px; width: 32px; height: 32px; border: 2px solid; color: #ffffff; background-color: #3b3b3b;}
        .submit_btn {border-radius: 4px; border: 2px solid #ffffff; width: 980px; height: 30px; font-size: 1.2rem; font-family: "Raleway", "HelveticaNeue", "Helvetica Neue", Helvetica, Arial, sans-serif; color: #ffffff; background-color: #3b3b3b;}
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
                            }
                        }
                    }                   
                }
                };
                xhttp.open("GET", "/json.htm?type=devices&rid=6", true);
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
                xhttp.open("GET", "/json.htm", true);
                xhttp.send();
            }
            refresh_data();
            //setInterval(refresh_data, 3000);        
        </script>
    </head>
    <body>
    <center>
    <div class=\"container\">
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
                            <a href="/set_domo">
                                <img src=" data:image/png;base64,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">
                            </a>
                        </td>
                        <td width=70>
                            <a href="/set_aprs">
                                <img src=" data:image/jpeg;base64,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">
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
                        <td width=300><h2> <b id="title">wait...</b><b></b></h2></td
                    </tr>
                </table>
            </div>
        </section> 
        <section>
            <div class="grid-container full"><big><b>Integracja z domoticzem</b></big></div>
            <form action="/save_domo" method="get">
            <div class="grid-container quarters">
                <div>
                    <label for="domoti_IP">Adres IP domoticza</label><br>
                    <input class="input_short" name="domoti_IP_1" id="domoti_IP_1" type="text" type="number" min="0" max="254" title="adres IP servera domoticz" placeholder="192">.
                    <input class="input_short" name="domoti_IP_2" id="domoti_IP_2" type="text" type="number" min="0" max="254" title="adres IP servera domoticz" placeholder="168">.
                    <input class="input_short" name="domoti_IP_3" id="domoti_IP_3" type="text" type="number" min="0" max="254" title="adres IP servera domoticz" placeholder="0">.
                    <input class="input_short" name="domoti_IP_4" id="domoti_IP_4" type="text" type="number" min="0" max="254" title="adres IP servera domoticz" placeholder="1">
                </div> 
                <div>
                    <label for="domoti_PORT">Port komunikacyjny</label>
                    <input class="input" name="domoti_PORT" id="domoti_PORT" type="text"  title="port" placeholder="80">
                </div>   
                <div>
                    <label for="send_interval">Interwał wysyłki danych</label>
                    <input class="input" name="send_interval" id="send_interval" type="number" min="1" max="10" step="1" title="interwał wysyłki danych w minutach" placeholder="10">
                </div>  
                <div>
                    <label for="domoti_on">Włącz integrację</label><br>
                    <input class="box" name="domoti_on" id="domoti_on" type="checkbox" value="1" title="włącz integrację z domoticzem"> 
                </div>                                            
            </div>
            <div class="grid-container quarters">
                <div>
                    <label for="idx_temp_rh_baro_sensor">IDX czujnika temp/Rh/baro</label>
                    <input class="input" name="idx_temp_rh_baro_sensor" id="idx_temp_rh_baro_sensor" type="text"  title="wpisz IDX czujnika wilgotności" placeholder="1">
                </div>   
                <div>
                    <label for="idx_wind_sensor">IDX czujnika wiatru</label>
                    <input class="input" name="idx_wind_sensor" id="idx_wind_sensor" type="text"  title="wpisz IDX czujnika temperatury" placeholder="2">
                </div>                  
            </div>
            <div>&nbsp;</div>
            <div>
                <input class="submit_btn" type="submit" value="zapisz" title="...">
            </div> 
            </form>  
        <div>
            &nbsp;
        </div>          
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