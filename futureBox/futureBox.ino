#include <Adafruit_Thermal.h>

#include "SoftwareSerial.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor



String arc1List[] = {"collapse", "discipline", "grow", "transform"};
String arc2List[] = {"a few years", "a decade", "a generation", "two generations", "a century", "a millennium"};
String terrainList[] = {"agriculture", "the brain", "childhood", "citizenship", "class", "climate", "cloning", "communications", "court", "disease", "drones", "the economy", "education", "entertainment", "environment", "equality", "family", "fashion", "flight", "forests", "genetics", "gender", "governance", "health", "hobbies", "home", "identity", "insects", "intellectual property", "journalism", "justice", "learning", "memory", "mining", "the moon", "music", "oceans", "oil", "old age", "pets", "power", "religion", "robots", "sex", "shopping", "space", "sports", "theatre", "travel", "war", "water", "wealth", "women", "work", "zombies", "the zoo", "wildcard (topic or location of your choice)"};
String objectList[] = {"advertisement", "artwork", "beverage", "book", "bottle", "box", "brochure", "building", "candy", "clothing", "corporation", "device", "document", "event", "festival", "flag", "game", "gift", "headline", "implant", "instrument", "jewellery", "kit", "law", "logo", "lotion", "machine", "magazine cover", "map", "mask", "monument", "passport", "pill", "plant", "postcard", "poster", "product", "prosthetic", "public service announcement", "relic", "ritual", "show", "slogan", "snack", "song", "souvenir", "statue", "sticker", "symbol", "t-shirt", "tattoo", "tool", "toy", "vehicle", "video", "weapon", "wildcard (artifact of your choice)"};
String moodList[] = {"admiration", "alienation", "amusement", "anger", "anxiety", "awkwardness", "calm", "charm", "cheer", "contentment", "curiosity", "decadence", "delight", "dignity", "disgust", "dread", "embarrassment", "excitement", "exhilaration", "fascination", "fervor", "frustration", "gratitude", "happiness", "hilarity", "hope", "longing", "malaise", "melancholy", "melodrama", "nostalgia", "optimism", "outrage", "pathos", "pleasure", "pride", "rationality", "relief", "resentment", "respect", "sadness", "satisfaction", "serenity", "shame", "shock", "sorrow", "surprise", "unease", "warmth", "weirdness", "wellbeing", "wonder", "worry", "zen"};

int button = 3;
boolean lastButton = HIGH;

void setup() {
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);

  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial
}

void loop() {
  int currentButton = digitalRead(button);
  if (!currentButton && lastButton) {
    String arc1 = arc1List[random(4)];
    String arc2 = arc2List[random(6)];
    String terrain = terrainList[random(57)];
    String object = objectList[random(57)];
    String mood = moodList[random(54)];
    Serial.println("Arc");
    Serial.println(arc1);
    Serial.println(arc2);
    Serial.println();
    Serial.println("Terrain");
    Serial.println(terrain);
    Serial.println();
    Serial.println("Object");
    Serial.println(object);
    Serial.println();
    Serial.println("Mood");
    Serial.println(mood);
    Serial.println();

    printer.println("");
    
    printer.boldOn();
    printer.println("Arc");
    printer.boldOff();
    
    printer.println(arc1);
    printer.println(arc2);
    printer.println();
    
    printer.boldOn();
    printer.println("Terrain");
    printer.boldOff();

    printer.println(terrain);
    printer.println();
    
    printer.boldOn();
    printer.println("Object");
    printer.boldOff();
    
    printer.println(object);
    printer.println();
    
    printer.boldOn();
    printer.println("Mood");
    printer.boldOff();
    
    printer.println(mood);
    printer.println(" ");

  };
  lastButton = currentButton;
}
