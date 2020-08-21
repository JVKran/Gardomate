# Greenhouse
When eating a salad, it’s always nice to have some herbs to go with it. However, to get those herbs, they first have to grow. And to grow they need… You guessed it, water. Watering isn’t everyones strongest point. It isn’t mine either. That’s how I’ve come up with the idea to create an automated greenhouse; Gardomate. Gardomate stands for Garden Automate.

When we’re going to do this, let’s just go all-in. Not just watering, but also temperature and humidity control with a fan. I also planned on adding growlights, but that hasn’t been possible yet due to shipment delays. I’ll add them when they arrive.

Since this greenhouse is pretty large, I needed to really step up my game with this irrigation plan; the area that needs to be covered is pretty large… I needed approximately 2 meters of food-safe silicone tube and a food-safe peristaltic pump that’s powerful enough to push the water through the holes. All in all the first test was succesful.


<iframe width="560" height="315" src="https://www.youtube.com/embed/V8b7QdYzBEY" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>


The tape is just temporary; I’m trying to limit my movements due to the pandemic and picked up this food-safe silicone kit when I was near a shop that sold them. Furthermore, I needed to measure when it would be time to water the herbs. That’s done with a capacitive soil moisture sensor that’s embedded in the soil. The wires are located next to the water tube.

![](https://i1.wp.com/jochemvk.duckdns.org/wp-content/uploads/2020/08/Back.jpg?resize=640%2C479&ssl=1)

Since we also wanted to measure the relative humidity of the air in the greenhouse, a BME280 is used in combination with a fan. The fan is very suitable for lowering the moisture and turns on approximately every 10 minutes to bring the humidity down to the desired level.

Schematic
The peristaltic pump runs on 12V. An LM2596 Step-Down is used to convert the 12V to 5V for the D1 Mini, BME280 and Fan. By using two grounds the D1 Mini and Fan share one ground and the soil moisture sensor and BME280 share one ground. This makes sure readings are accurate and not interfered by voltage drops of Wifi-Transmissions or the fan turning on.
