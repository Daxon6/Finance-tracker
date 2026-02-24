package orion.rs.demo.domain;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Entity
@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor

public class Account {
    @Id
    @GeneratedValue
    private Long id;

    private AccountType type;
    private double balance;
    private String currency;
    @Version
    private int version;
    @ManyToOne
    private Employee employee;

}
