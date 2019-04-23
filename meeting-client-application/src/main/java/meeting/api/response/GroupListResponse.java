package meeting.api.response;

import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

@Data
@NoArgsConstructor
public class GroupListResponse {

    private List<GroupListItemResponse> items;
}
