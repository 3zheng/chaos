CREATE PROCEDURE [dbo].[get_user_best_rank]
	@user_id bigint 
	
AS
--获得用户的最佳排名和夺冠次数
	SELECT * from user_exploits_info where user_id = @user_id
RETURN 0
