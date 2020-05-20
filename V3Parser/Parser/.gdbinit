#b 'HkProfiler::extract(std::istream *, char *)'
#b 'HkTradeExtract::output()'
#b 'HkTradeExtract::findCompanyName(char *)'
#set args pro03933.html
#set args pro02727.html
#set args pro00606.html
#set args ~/AkraLog/Projets/Fino/CertaintyAmpl/Dev/trunk/DataAcquiz/HkEx/Pages/TradeInfo/Content/00002.html
#b 'HomeDepoter::inspect_B(HtScanner *, PageHD*)'
#b 'HomeDepoter::extract(std::istream*, char*)'
#set args /tmp/frontPage.html
#set args -p 7 /home/hugo/AkraLog/Projets/Immobilier/HongKong/DataAcquisition/GoHome/nss/1.html
b 'HomeDepoter::doWork()'
