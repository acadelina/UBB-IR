package ubb.scs.map.domain.validators;


import ubb.scs.map.domain.User;

public class UserValidator implements Validator<User> {
    @Override
    public void validate(User entity) throws ValidationException {
        if(entity==null)
            throw new ValidationException("User can't be empty");
        if(entity.getFirstName().equals(""))
            throw new ValidationException("First name can't be empty!");
        if(entity.getLastName().equals(""))
            throw new ValidationException("Last name can't be empty!");
        if(entity.getId()==null)
            throw new ValidationException("ID can't be empty!");
    }
}
