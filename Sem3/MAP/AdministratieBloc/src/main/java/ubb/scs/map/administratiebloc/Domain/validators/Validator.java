package ubb.scs.map.administratiebloc.Domain.validators;

public interface Validator <T> {
    void validate(T entity) throws ValidationException;
}