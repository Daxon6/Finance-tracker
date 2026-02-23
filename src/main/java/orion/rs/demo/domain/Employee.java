package orion.rs.demo.domain;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

@Entity
@Getter
@Setter
public class Employee {

    @Id
    @GeneratedValue
    private Long id;

    private String firstname;
    private String lastname;

    private String email;

}
