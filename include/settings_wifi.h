const char HTTP_WIFI[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pl" style="height:100;">
    <head>
     <meta charset="UTF-8">
     <style>
        body { font-size: 1.2rem; line-height: 1.6; font-weight: 300;font-family: "Segoe UI Bold", "HelveticaNeue", "Helvetica Neue", Helvetica, Arial, sans-serif; color: #ffffff; background-color: #4b4b4b;}
        small {font-size: 0.7rem; }
        .big {font-size: 1.8rem; font-weight: 1000;}
        .med {font-size: 1.2rem; font-weight: 500;}
        .container {position: relative; margin: 0 auto;}
        .grid-container {position: relative;max-width: var(--grid-max-width);margin: 0 auto;padding: 10px;text-align: center;display: grid; grid-gap: 10px;gap: 10px;}
        .grid-container.quarters { grid-template-columns: repeat(4, 1fr); border-radius: 4px;}
        .grid-container.half { grid-template-columns: repeat(2, 1fr); border-radius: 4px;}
        section { border-radius: 4px; border: 2px solid #ffffff; margin-top: 5px; padding: 5px; max-width: 1024px; }
        .input {border-radius: 4px; border: 2px solid #ffffff; width: 200px; height: 30px; font-size: 1.2rem; font-family: "Segoe UI Bold", "HelveticaNeue", "Helvetica Neue", Helvetica, Arial, sans-serif; color: #ffffff; background-color: #3b3b3b;}
        .input_long {border-radius: 4px; border: 2px solid #ffffff; width: 450px; height: 30px; font-size: 1.2rem; font-family: "Segoe UI Bold", "HelveticaNeue", "Helvetica Neue", Helvetica, Arial, sans-serif; color: #ffffff; background-color: #3b3b3b;}
        .input_short {border-radius: 4px; border: 2px solid #ffffff; width: 37px; height: 30px; font-size: 1.2rem; font-family: "Segoe UI Bold", "HelveticaNeue", "Helvetica Neue", Helvetica, Arial, sans-serif; color: #ffffff; background-color: #3b3b3b;}
        .box {border-radius: 4px; width: 32px; height: 32px; border: 2px solid; color: #ffffff; background-color: #3b3b3b;}
        .submit_btn {border-radius: 4px; border: 2px solid #ffffff; width: 974px; height: 30px; font-size: 1.2rem; font-family: "Segoe UI Bold", "HelveticaNeue", "Helvetica Neue", Helvetica, Arial, sans-serif; color: #ffffff; background-color: #3b3b3b;}
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
                xhttp.open("GET", "/json.htm?type=devices&rid=3", true);
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
        </script>
    </head>
    <body>
    <center>
        <header>
            <div>
                <img src="data:image/png;base64,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">
            </div>
        </header>           
    <div class="container">
        <section>
            <div class="grid-container full">
                <table cellspacing=0 cellpadding=0 border=0>
                    <tr>
                        <td width=70>
                            <a href="/">
                                <img src=" data:image/png;base64,/9j/4AAQSkZJRgABAQEAWgBaAAD/4gKwSUNDX1BST0ZJTEUAAQEAAAKgbGNtcwQwAABtbnRyUkdCIFhZWiAH5QAGAAoAEgALABthY3NwTVNGVAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA9tYAAQAAAADTLWxjbXMAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA1kZXNjAAABIAAAAEBjcHJ0AAABYAAAADZ3dHB0AAABmAAAABRjaGFkAAABrAAAACxyWFlaAAAB2AAAABRiWFlaAAAB7AAAABRnWFlaAAACAAAAABRyVFJDAAACFAAAACBnVFJDAAACFAAAACBiVFJDAAACFAAAACBjaHJtAAACNAAAACRkbW5kAAACWAAAACRkbWRkAAACfAAAACRtbHVjAAAAAAAAAAEAAAAMZW5VUwAAACQAAAAcAEcASQBNAFAAIABiAHUAaQBsAHQALQBpAG4AIABzAFIARwBCbWx1YwAAAAAAAAABAAAADGVuVVMAAAAaAAAAHABQAHUAYgBsAGkAYwAgAEQAbwBtAGEAaQBuAABYWVogAAAAAAAA9tYAAQAAAADTLXNmMzIAAAAAAAEMQgAABd7///MlAAAHkwAA/ZD///uh///9ogAAA9wAAMBuWFlaIAAAAAAAAG+gAAA49QAAA5BYWVogAAAAAAAAJJ8AAA+EAAC2xFhZWiAAAAAAAABilwAAt4cAABjZcGFyYQAAAAAAAwAAAAJmZgAA8qcAAA1ZAAAT0AAACltjaHJtAAAAAAADAAAAAKPXAABUfAAATM0AAJmaAAAmZwAAD1xtbHVjAAAAAAAAAAEAAAAMZW5VUwAAAAgAAAAcAEcASQBNAFBtbHVjAAAAAAAAAAEAAAAMZW5VUwAAAAgAAAAcAHMAUgBHAEL/2wBDAAMCAgMCAgMDAwMEAwMEBQgFBQQEBQoHBwYIDAoMDAsKCwsNDhIQDQ4RDgsLEBYQERMUFRUVDA8XGBYUGBIUFRT/2wBDAQMEBAUEBQkFBQkUDQsNFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBT/wgARCAAwADADAREAAhEBAxEB/8QAGgABAAIDAQAAAAAAAAAAAAAABwAGAQMFAv/EABQBAQAAAAAAAAAAAAAAAAAAAAD/2gAMAwEAAhADEAAAATgg2HoEjBBnDkwJALjoGJWSFmE46gBi4QIx8K6G53iHBEgybimkLkaT/8QAIhAAAgEEAAcBAAAAAAAAAAAABAUGAQIDBxAREiIyNTYA/9oACAEBAAEFAuCRQPGAXKkeVg8UKTAgCduyHpqR0QiNfJR5CF+h0Q6LH77O/N4IX2dAZMYj12RF8W9zBjXGl11tfbWmtr7qmDVCMlz4tFm1x5IPezn6mDfUv/e7H8ta92ZZr1iEynFecpg9eUpZ69Ymstldub//xAAUEQEAAAAAAAAAAAAAAAAAAABQ/9oACAEDAQE/ARP/xAAUEQEAAAAAAAAAAAAAAAAAAABQ/9oACAECAQE/ARP/xAAzEAABAgQBBwsFAQAAAAAAAAABAgMABAURMRIhQWGCsbIQFSJDcXN0ocHR4SAjM0KB8f/aAAgBAQAGPwLkFXqo+/1Eucf93RztSxaYH55fST77/o55qwsRnYlzjfR/YL75sMENjBAgPsHN+6DgsRzzSBdXXy4xv78gqU+3mAymmTvMF53otjM23oSOUPNG7ZzON6FCDUpBvHpOsjeIn1TSwchkBKUiwGMMS6SAp1YQCdZixqTIOtPzFhUmSdSfmH5dRBU0soJGoxIKlVgZbJCkqFwcIqfdD1ineJb4hE7scCYktvgVFR8S5xGKZ3R9IqKLjKU0LecSkwt6WKGnUrISpV7A9kTuxwCJLb4DE3MIelgh11SwFKVexPZFORcZSWjfyj//xAAmEAEAAQIFAgcBAAAAAAAAAAABEQAhMUFRYXGB0RAgkaGx8PHB/9oACAEBAAE/Iaiau898AcrfXLBScVjkW+uVJDDZ8S0YQF+ZHsMsXaNY3Din9c6lGYFcF75UqksoOZj3GeJvRSdC3rF8HWkAZIX9Wr4tSipf1aNGjAY3rF8nWjkGuEjGrWGSfgQCfWo01kpQktZStMOEvCoSelHINMJGNTzuNsvmzgDQBC791TE58gVjXaiSIllqSSoFl6Yic+RKTrvQHUBA79lf/9oADAMBAAIAAwAAABCSQSSASSQQACASSCAAT//EABQRAQAAAAAAAAAAAAAAAAAAAFD/2gAIAQMBAT8QE//EABQRAQAAAAAAAAAAAAAAAAAAAFD/2gAIAQIBAT8QE//EAB8QAQEAAgICAwEAAAAAAAAAAAERITEAQVFxEGGB8P/aAAgBAQABPxDgkAKuAO+YYxCLSpffecDLwk7cAkKgdTImBE6KMCDETI/M33AFJVe3tMGyTnMgi5ox5l3sXgAKD6NCzPjfGyz5GBKjACUjo2hgyi/FgewMwh3qt7dcfSVNr19uD2PgAPhrCQ47p8GrsHyKO9yMwJRvdL075mv71jsnQV+gIE5QsDt8ozBF4z3iaH48ayxMTvRxba3980zFScxX9+x2RsY/aNGc/q+fjQa1dY/JBQ/q+eYuVBXAs3BF98SJ3iCwSKFKhezh+00VKGn4ifnH9pooVMP1Q/eBE7xBYDAAsUvbyrlQUwDNxVPXP//Z">
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
            <div class="grid-container full"><big><b>Ustawienia sieci WiFi</b></big></div>
            <form action="/save_wifi" method="get">
                <div class="grid-container half">
                    <div class="grid-container full">
                        <div>
                            <label for="wifi_ssid">WiFi SSID</label>
                            <input class="input_long" name="wifi_ssid" id="wifi_ssid" type="text"  title="Nazwa sieci">
                        </div> 
                    </div> 
                    <div class="grid-container full">
                        <div>
                            <label for="wifi_pass">WiFi password</label>
                            <input class="input_long" name="wifi_pass" id="wifi_pass" type="password"  title="hasło do sieci WiFi">
                        </div> 
                    </div> 
                </div>
                <div class="grid-container full">
                    <div>
                        <input class="submit_btn" type="submit" value="zapisz i zrestartuj" title="...">
                    </div>                     
                </div>
            </form>
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