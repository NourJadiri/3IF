#include <iostream>
#include <regex>
#include "Log.h"

using namespace std;

int main(){

    const string log = "192.168.0.11 - - [08/Sep/2012:12:01:18 +0200] \"GET /notesif HTTP/1.1\" 301 248 \"https://intranet-if.insa-lyon.fr/temps/zizi\" \"Tiny Tiny RSS/1.5.11 (http://tt-rss.org/)\"";
    Log * aLog = new Log(log);

    cout << aLog->getLongReferer() << endl;

    cout << get_path_from_url( aLog->getLongReferer() ) << endl;

    cout << aLog->getShortReferer() << endl;

    cout << aLog->getDocumentRequested() << endl;

    cout << aLog->getHeureConsultation() << endl;

    cout << aLog->getReturnCode() << endl;

    delete aLog;
    return 0;
}
