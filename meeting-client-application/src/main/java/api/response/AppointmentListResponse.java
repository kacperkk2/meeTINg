package api.response;

import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

@Data
@NoArgsConstructor
public class AppointmentListResponse {

    private List<AppointmentListItemResponse> items;
}
