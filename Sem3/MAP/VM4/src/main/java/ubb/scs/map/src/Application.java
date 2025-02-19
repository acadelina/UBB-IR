package ubb.scs.map.src;

import ubb.scs.map.src.repository.CustomerRepository;
import ubb.scs.map.src.repository.CustomerRepositoryImpl;
import ubb.scs.map.src.repository.VehicleRepository;
import ubb.scs.map.src.repository.VehicleRepositoryImpl;
import ubb.scs.map.src.service.VehicleService;
import ubb.scs.map.src.service.VehicleServiceImpl;
import ubb.scs.map.src.ui.ConsoleUI;

public class Application {

	public static void main(String[] args) {
		VehicleRepository vehicleRepository = new VehicleRepositoryImpl();
		VehicleService vehicleService = new VehicleServiceImpl(vehicleRepository);
		CustomerRepository customerRepository = new CustomerRepositoryImpl();
		ConsoleUI consoleUI = new ConsoleUI(vehicleService,customerRepository);
		consoleUI.displayVehicles();
		
		System.out.println("---------------------------");
		consoleUI.displayCustomers();
		
		System.out.println("----------------------------");
		consoleUI.addCustomer();
		
		System.out.println("-----------------------------");
		consoleUI.displayCustomers();	
	}

}
