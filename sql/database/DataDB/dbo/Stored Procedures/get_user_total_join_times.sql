CREATE PROCEDURE [dbo].[get_user_total_join_times]
	@user_id bigint,
	@plan_id int
AS
--找到某个用户的某赛事的总参赛次数
	SELECT user_id, plan_id, sum(join_times) from user_join_times 
	where user_id = @user_id and plan_id = @plan_id group by user_id, plan_id
RETURN 0
