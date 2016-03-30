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

// The physical switches goes from these to a ground on the middle leg of the switch
int arc1Switch = 22;
int arc2Switch = 23;
int terrainSwitch = 24;
int objectSwitch = 25;
int moodSwitch = 26;

// Button goes from here to ground
int button = 3;
boolean lastButton = HIGH;

// This var decides how many empty lines are printed after the prompt. Change according to the box the printer is put in
int endPadding = 4;

// These two vars sets the size of the category names and the contents. 'L' for large, 'M' for medium and 'S' for small
char categorySize = 'M';
char contentSize = 'S';

void setup() {
  pinMode(arc1Switch, INPUT_PULLUP);
  pinMode(arc2Switch, INPUT_PULLUP);
  pinMode(terrainSwitch, INPUT_PULLUP);
  pinMode(objectSwitch, INPUT_PULLUP);
  pinMode(moodSwitch, INPUT_PULLUP);

  pinMode(button, INPUT_PULLUP);


  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial
}

void loop() {
  int currentButton = digitalRead(button);
  if (!currentButton && lastButton) {
    printText();
  };
  lastButton = currentButton;
}

void printText() {
  String arc1 = arc1List[random(4)];
  String arc2 = arc2List[random(6)];
  String terrain = terrainList[random(57)];
  String object = objectList[random(57)];
  String mood = moodList[random(54)];

  boolean arc1State = digitalRead(arc1Switch);
  boolean arc2State = digitalRead(arc2Switch);
  boolean terrainState = digitalRead(terrainSwitch);
  boolean objectState = digitalRead(objectSwitch);
  boolean moodState = digitalRead(moodSwitch);

  if (arc1State || arc2State) {
    printer.setSize(categorySize);
    printer.println("Arc");
    printer.setSize(contentSize);
    if (arc1State) {
      printer.println(arc1);
    }
    if (arc2State) {
      printer.println(arc2);
    }
  }

  if (terrainState) {
    printer.feed(1);

    printer.setSize(categorySize);
    printer.println("Terrain");
    printer.setSize(contentSize);

    printer.println(terrain);
  }

  if (objectState) {
    printer.feed(1);
    printer.setSize(categorySize);
    printer.println("Object");
    printer.setSize(contentSize);
    printer.println(object);
  }

  if (moodState) {
    printer.feed(1);
    printer.setSize(categorySize);
    printer.println("Mood");
    printer.setSize(contentSize);
    printer.println(mood);
  }

  if (!arc1State && !arc2State && !terrainState && !objectState && !moodState) {
    printer.setSize('M');
    printer.println("There is no future");
  }
  printer.feed(endPadding);


}
