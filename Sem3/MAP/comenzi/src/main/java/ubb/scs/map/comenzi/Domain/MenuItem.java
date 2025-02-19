package ubb.scs.map.comenzi.Domain;

import javafx.beans.property.SimpleBooleanProperty;
import javafx.scene.control.CheckBox;

public class MenuItem extends Entity<Integer> {
    String category;
    String item;
    Float price;
    String currency;
    private boolean selected;

    public MenuItem(String currency, Float price, String item, String category) {
        this.currency = currency;
        this.price = price;
        this.item = item;
        this.category = category;
        this.selected =false;
    }

    public String getCategory() {
        return category;
    }

    public void setCategory(String category) {
        this.category = category;
    }

    public String getItem() {
        return item;
    }

    public void setItem(String item) {
        this.item = item;
    }

    public Float getPrice() {
        return price;
    }

    public void setPrice(Float price) {
        this.price = price;
    }

    public String getCurrency() {
        return currency;
    }

    public void setCurrency(String currency) {
        this.currency = currency;
    }

    public boolean isSelected() {
        return selected;
    }



    public void setSelected(boolean selected) {
        this.selected=selected;
    }
}
