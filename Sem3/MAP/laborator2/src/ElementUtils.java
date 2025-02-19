import java.util.List;

public class ElementUtils {
    public static <T> Object lastEntry(List<T> elements){
        return elements.get(elements.size()-1);
    }
}
