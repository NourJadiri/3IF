#include <iostream>
#include <regex>
#include "LogFile_Manager.h"

using namespace std;

int main(){

    const string log = "192.168.0.11 - - [08/Sep/2012:12:01:18 +0200] \"GET /notesif HTTP/1.1\" 301 248 \"https://intranet-if.insa-lyon.fr/temps/zizi\" \"Tiny Tiny RSS/1.5.11 (http://tt-rss.org/)\"";
/*    Log * aLog = new Log(log);

    cout << aLog->getLongReferer() << endl;

    cout << getPathFromUrl( aLog->getLongReferer() ) << endl;

    cout << aLog->getShortReferer() << endl;

    cout << aLog->getDocumentRequested() << endl;

    cout << aLog->getHeureConsultation() << endl;

    cout << aLog->getReturnCode() << endl;

    delete aLog;*/
/*    LogFile_Manager fileManager("../C++/TP4/Logs/short.log");

    fileManager.Display();*/

    return 0;
}
