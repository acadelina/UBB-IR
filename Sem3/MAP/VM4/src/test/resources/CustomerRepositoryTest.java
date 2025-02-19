import org.junit.Before;
import org.junit.Test;


import ubb.scs.map.src.domain.Customer;
import ubb.scs.map.src.repository.CustomerRepository;
import ubb.scs.map.src.repository.CustomerRepositoryImpl;

public class CustomerRepositoryTest {
	
	private CustomerRepository customerRepository;

	@Before
	public void setUp(){
		this.customerRepository = new CustomerRepositoryImpl();
	}
	
	@Test
	public void testAddCustomer(){
		Customer customer=new Customer("012","Ion",23);
		assertEqual(0,customerRepository.getAllCustomers().size());
		customerRepository.addCustomer(customer);
		assertEqual(1,customerRepository.getAllCustomers().size());

	}
}
