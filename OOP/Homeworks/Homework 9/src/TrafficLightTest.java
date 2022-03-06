
enum TrafficLight {
    RED(5),
    YELLOW(10),
    GREEN(15);

    private int time;

    TrafficLight(int time) {
        this.time = time;
    }

    public int getTime(){
        return time;
    }
}

public class TrafficLightTest {
	
    public static void main(String[] args) {

        for (TrafficLight light : TrafficLight.values()) {
            System.out.println(light + ": " + light.getTime() + " seconds");
        }
    }
}