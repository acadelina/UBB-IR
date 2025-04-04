package repository;

import java.util.ArrayList;
import java.util.Calendar;

import domain.Vehicle;

public class VehicleRepositoryImpl implements VehicleRepository {

	//TODO do we still need this variable since we are using List?
	//private static final Integer MAX_CAPACITY = 100;

	//TODO replace the array with a list. Use List<Vehicle> interface and ArrayList as implementation
	private ArrayList<Vehicle> vehicles;
	//TODO do we still need this variable since we are using List?
	private int numberOfVehicles;

	//TODO refactor constructor
	public VehicleRepositoryImpl() {
		this.numberOfVehicles = 0;// there are no vehicles into the stock
		vehicles = new ArrayList<Vehicle>();
	}

	//TODO refactor the method based on the list
	public void addVehicle(Vehicle newVehicle) {
		if (!newVehicle.isInactive()) {
			vehicles.add(newVehicle);
			numberOfVehicles++;
		} else {
			System.out.println("No vehicles can be added to the stock");
		}
	}

	//TODO refactor the method
	public Vehicle getVehicleAtPosition(int position) {
		return vehicles.get(position);
	}

	public int getNumberOfVehicles() {
		return numberOfVehicles;
	}

	//TODO refactor the method
	public ArrayList<Vehicle> getVehicles() {
		return vehicles;
	}

	@Override
	public void deleteVehicle(Vehicle vehicle) {
		Integer currentYear = Calendar.getInstance().get(Calendar.YEAR);

		if ((currentYear - vehicle.getYear()) > 30) {
			// we will delete the vehicle, mark it as being inactive
			vehicle.setInactive();
		}
	}
}
