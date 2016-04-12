CREATE PROCEDURE [dbo].[Procedure1]
	
AS
declare @user_id bigint;
	set @user_id = 1000000;
	while @user_id <= 1010000
	begin
		insert into user_fund(user_id, fund_id, fund_count, up_code, modify_time) values(@user_id, 100, 500000, 1, getdate());
	end
RETURN 0
