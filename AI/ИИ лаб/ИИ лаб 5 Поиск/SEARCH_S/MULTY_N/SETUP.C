void setup()
{
  assert_flight("New York","Chicago",1000);
  assert_flight("Chicago","Denver",1000);
  assert_flight("New York","Toronto",800);
  assert_flight("New York","Denver",1900);
  assert_flight("Toronto","Calgary",1500);
  assert_flight("Toronto","Los Angeles",1800);
  assert_flight("Toronto","Chicago",500);
  assert_flight("Denver","Urbana",1000);
  assert_flight("Denver","Houston",1500);
  assert_flight("Houston","Los Angeles",1500);
  assert_flight("Denver","Los Angeles",1000);

  assert_flight("С.-Петербург","Москва",640);
  assert_flight("С.-Петербург","Рига",480);
  assert_flight("Рига","Минск",410);
  assert_flight("Москва","Минск",660);
  assert_flight("Москва","Харьков", 650);
  assert_flight("Минск","Харьков",740);
  assert_flight("Минск","Киев",440);
  assert_flight("Москва","Киев",740);
  assert_flight("Киев","Харьков",410);
  assert_flight("Киев","Львов",470);
  assert_flight("Киев","Одесса",450);
  assert_flight("Львов","Одесса",620);
  assert_flight("Киев","Симферополь",660);
  assert_flight("Киев","Днепропетровск",390);
  assert_flight("Харьков","Одесса",560);
  assert_flight("Харьков","Симферополь",580);
  assert_flight("Харьков","Донецк",250);
  assert_flight("Донецк","Симферополь",440);
  assert_flight("Днепропетровск","Симферополь",400);
  assert_flight("Одесса","Симферополь",320);
  assert_flight("Симферополь","Одесса",320);
  return;
  }
