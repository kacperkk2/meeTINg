package meeting.api.request;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class UserDataRequest {
    // TODO myślę, że tego requesta można używać do rejestracji czy też innych requestów gdzie chodzi o wysłanie danych użytkownika - bo coś dużo podobno wyjdzie tych requestów nam

    private String username;

    private String password;
}
