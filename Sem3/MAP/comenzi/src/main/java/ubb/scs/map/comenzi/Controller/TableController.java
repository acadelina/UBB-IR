package ubb.scs.map.comenzi.Controller;

import javafx.beans.property.SimpleBooleanProperty;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.CheckBoxTableCell;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import ubb.scs.map.comenzi.Domain.MenuItem;
import ubb.scs.map.comenzi.Service.Service;
import ubb.scs.map.comenzi.observer.Observer;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class TableController implements Observer {

    @FXML
    VBox vbox;


    private Map<Integer, Boolean> selectionMap = new HashMap<>();

    Service service;
    Integer tableId;
    Stage stage;
    List<TableView> tableViews=new ArrayList<>();

    TableColumn nume=new TableColumn("Nume");
    TableColumn price=new TableColumn("Price");
    TableColumn check=new TableColumn("Check");

    public void createTable(String categorie, List<MenuItem> items)
    {
        TableView tableView=new TableView();
        tableView.setEditable(true);
        nume.setCellValueFactory(new PropertyValueFactory<>("nume"));
        price.setCellValueFactory(new PropertyValueFactory<>("price"));
        check.setCellValueFactory(c->new CheckBoxTableCell());
        tableView.getColumns().addAll(nume,price,check);
        tableView.setItems((ObservableList<MenuItem>)items);
        tableViews.add(tableView);
        vbox.getChildren().add(tableView);
    }
    List<Integer> order=new ArrayList<>();

    public void init() {
        // Obținem categoriile și elementele din meniu
        Map<String, List<MenuItem>> meniu = service.categorii();

        // Curățăm orice tabel anterior
        vbox.getChildren().clear();

        // Creăm un tabel pentru fiecare categorie
        for (String categorie : meniu.keySet()) {
            // Creăm tabelul
            TableView<MenuItem> tableView = new TableView<>();
            tableView.setPrefWidth(600); // Setăm dimensiunea tabelului
            tableView.setEditable(true);
            // Creăm coloanele
            TableColumn<MenuItem, String> nameColumn = new TableColumn<>("Name");
            nameColumn.setCellValueFactory(new PropertyValueFactory<>("item"));

            TableColumn<MenuItem, Double> priceColumn = new TableColumn<>("Price");
            priceColumn.setCellValueFactory(new PropertyValueFactory<>("price"));



            // Adăugăm coloana cu CheckBox
            TableColumn<MenuItem, Boolean> selectColumn = new TableColumn<>("Select");
            selectColumn.setCellValueFactory(data -> {
                // Legăm un `SimpleBooleanProperty` de fiecare item
                MenuItem item = data.getValue();
                SimpleBooleanProperty selectedProperty = new SimpleBooleanProperty(false);

                // Listener pentru schimbarea valorii (opțional)
                selectedProperty.addListener((obs, oldValue, newValue) -> {
                    if(newValue==true)
                        order.add(item.getId());
                    else
                        order.remove(item.getId());

                });

                return selectedProperty;
            });

            // Setăm celulele să folosească `CheckBoxTableCell`
            selectColumn.setCellFactory(CheckBoxTableCell.forTableColumn(selectColumn));

            // Adăugăm coloanele în tabel
            tableView.getColumns().addAll(nameColumn, priceColumn, selectColumn);

            // Setăm datele din categoria curentă
            tableView.getItems().addAll(meniu.get(categorie));

            // Adăugăm un titlu (numele categoriei) deasupra fiecărui tabel
            Label categoryLabel = new Label(categorie);
            categoryLabel.setStyle("-fx-font-size: 16px; -fx-font-weight: bold;");

            // Adăugăm label-ul și tabelul în containerul principal
            vbox.getChildren().addAll(categoryLabel, tableView);


        } Button button=new Button("Order");
        button.setOnAction(event -> handlePlaceOrder());
        vbox.getChildren().add(button);
    }


    private void handlePlaceOrder() {
        List<Integer> selectedItems = new ArrayList<>();

        service.placeOrder(tableId,order,LocalDateTime.now());
        update();
    }

    @Override
    public void update() {

    }

    public void setService(Service service, Integer tableId, Stage stage) {
        this.service = service;
        this.tableId = tableId;
        this.stage = stage;
        service.addObserver(this);
    }


}
