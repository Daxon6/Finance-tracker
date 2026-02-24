package orion.rs.demo.domain;

import jakarta.persistence.*;
import jakarta.validation.constraints.Email;
import lombok.Getter;
import lombok.Setter;

import java.util.ArrayList;
import java.util.List;

@Entity
@Getter
@Setter
public class Employee {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String firstname;
    private String lastname;

    @Email//da mora da bude u dobrom formatu
    private String email;

    @OneToMany(mappedBy = "employee", cascade = CascadeType.ALL)
    private List<Account> employeeAcounts = new ArrayList<>();

}
