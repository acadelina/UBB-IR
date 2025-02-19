import java.util.HashMap;
import java.util.Map;

public class MyMap {
    private HashMap<String, String> map;
    public MyMap() {
        map = new HashMap<String,String>();
    }
    public void put(String key, String value) {
        map.put(key.toLowerCase(), value);
    }

    public Map<String,String> get() {

        return map;
    }

}
