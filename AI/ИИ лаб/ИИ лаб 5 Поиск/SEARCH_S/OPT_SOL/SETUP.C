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
  return;
}