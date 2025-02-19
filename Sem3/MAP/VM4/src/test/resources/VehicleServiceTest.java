import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;

import org.junit.Before;
import org.junit.Test;

import ubb.scs.map.src.domain.Vehicle;
import ubb.scs.map.src.repository.VehicleRepository;
import ubb.scs.map.src.repository.VehicleRepositoryImpl;
import ubb.scs.map.src.service.VehicleService;
import ubb.scs.map.src.service.VehicleServiceImpl;


public class VehicleServiceTest {
	
	private static final String LICENSE_PLATE="CJ09RMN";
	private static final String PROPERTY_TO_LOAD_DATA="vehicleTestLoadFile";
	
	private VehicleService vehicleService;
	private VehicleRepository vehicleRepository;
	
	@Before
	public void setUp(){
		vehicleRepository = new VehicleRepositoryImpl();
		vehicleService = new VehicleServiceImpl(vehicleRepository);
		vehicleRepository.initialLoadOfVehicles(PROPERTY_TO_LOAD_DATA);
	}
	
	@Test
	public void testSearchVehiclesWhenValidLicensePlate(){
		//when
		Vehicle foundVehicle  = vehicleService.searchVehicle(LICENSE_PLATE);
		
		//then
		assertNotNull(foundVehicle);
		assertEquals(LICENSE_PLATE,foundVehicle.getLicensePlate());
	}
	
	@Test
	public void searchVehiclesWhenWrongLicensePlate(){
		//when
		Vehicle noVehicle = vehicleService.searchVehicle("ZMS12");
		
		//then
		assertNull(noVehicle);
	}

}
