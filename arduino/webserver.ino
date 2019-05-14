// DNSServer had to be patched, info found here: https://github.com/espressif/arduino-esp32/issues/1037
#include "./DNSServer.h"
#include <ESP8266WebServer.h>
#include <FS.h>

const char *softAP_ssid = "CaptainQuack";
const byte DNS_PORT = 53;
DNSServer dnsServer;
ESP8266WebServer server(80);
IPAddress netMsk(255, 255, 255, 0);

// android os requires the dns ip not be in the 'local ip' range, so don't use stuff like 192.168.x.x 
IPAddress apIP(172, 217, 28, 1);

void Webserver_Init()
{
    // setup the access point and give the it a moment to bring the access point online
    WiFi.softAPConfig(apIP, apIP, netMsk);
    WiFi.softAP(softAP_ssid);
    delay(500);

    // setup the dns server to redirect all dns requests to the web servers ip address
    dnsServer.setTTL(300);
    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    dnsServer.start(DNS_PORT, "*", apIP);
    SPIFFS.begin();

    // setup all of the api endpoints for the control webpage to use
    server.on(
        "/leftStart",
        []() {
            leftStart();
            send200OK();
        });

    server.on(
        "/leftStop",
        []() {
            leftStop();
            send200OK();
        });

    server.on(
        "/rightStart",
        []() {
            rightStart();
            send200OK();
        });

    server.on(
        "/rightStop",
        []() {
            rightStop();
            send200OK();
        });

    // if the url doesn't get picked up as an api endpoint, assume it's a file from SPIFFS
    server.onNotFound(
        []() {
            // if the url is not recognized as an api endpoint and doesn't match a local file, 
            // redirect it to /index.html
            if (!handleFileRead(server.uri()))
                redirectToIndex();
        });

    server.begin();
}

void Webserver_Update(void)
{
    // dns server update
    dnsServer.processNextRequest();

    // http server update
    server.handleClient();
}

// send the right file to the client (if it exists)
bool handleFileRead(String path)
{
    // If a folder is requested, send the index file
    if (path.endsWith("/"))
        path += "index.html";

    // Get the MIME type
    String contentType = getContentType(path);

    // does this file exist in SPIFFS?
    if (SPIFFS.exists(path))
    {
        // send it
        File file = SPIFFS.open(path, "r");
        size_t sent = server.streamFile(file, contentType);
        file.close();
        return true;
    }

    // If the file doesn't exist, return false
    return false;
}

void redirectToIndex()
{
    server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    server.sendHeader("Pragma", "no-cache");
    server.sendHeader("Expires", "-1");
    server.sendHeader("Location", String("http://") + String(apIP[0]) + "." + String(apIP[1]) + "." + String(apIP[2]) + "." + String(apIP[3]) + String("/index.html"), true);
    server.send(302, "text/plain", "");
    server.client().stop();
}

void send200OK()
{
    // note: we're 'cache busting' all of these responses so the browser re-requests the api every time
    server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    server.sendHeader("Pragma", "no-cache");
    server.sendHeader("Expires", "-1");
    server.send(200, "text/html", "OK");
    server.client().stop();
}

String getContentType(String filename)
{
    if (filename.endsWith(".htm"))
        return "text/html";
    else if (filename.endsWith(".html"))
        return "text/html";
    else if (filename.endsWith(".css"))
        return "text/css";
    else if (filename.endsWith(".js"))
        return "application/javascript";
    else if (filename.endsWith(".png"))
        return "image/png";
    else if (filename.endsWith(".gif"))
        return "image/gif";
    else if (filename.endsWith(".jpg"))
        return "image/jpeg";
    else if (filename.endsWith(".ico"))
        return "image/x-icon";
    else if (filename.endsWith(".xml"))
        return "text/xml";
    else if (filename.endsWith(".pdf"))
        return "application/x-pdf";
    else if (filename.endsWith(".zip"))
        return "application/x-zip";
    else if (filename.endsWith(".gz"))
        return "application/x-gzip";
    return "text/plain";
}
