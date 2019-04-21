package api.response;

import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
public class UserLoginResponse {

    private long id;

    private String username;

    private String password;

    private String systemRole;
}
